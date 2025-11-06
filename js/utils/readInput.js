const fs = require('fs');
const path = require('path');
const https = require('https');

// Load configuration
function loadConfig() {
    const configPath = path.join(__dirname, 'config.env');
    let config = {
        AOC_SESSION: null,
        AOC_EMAIL: 'your-email@example.com'
    };
    
    if (fs.existsSync(configPath)) {
        const configContent = fs.readFileSync(configPath, 'utf8');
        const lines = configContent.split('\n');
        
        for (const line of lines) {
            const trimmed = line.trim();
            if (trimmed && !trimmed.startsWith('#')) {
                const [key, value] = trimmed.split('=');
                if (key && value) {
                    config[key.trim()] = value.trim();
                }
            }
        }
    }
    
    // Fallback to environment variables
    config.AOC_SESSION = config.AOC_SESSION || process.env.AOC_SESSION;
    config.AOC_EMAIL = config.AOC_EMAIL || process.env.AOC_EMAIL || 'your-email@example.com';
    
    return config;
}

const config = loadConfig();

/**
 * Reads Advent of Code input data for a given year and day
 * @param {number} year - The year (e.g., 2019)
 * @param {number} day - The day (e.g., 2)
 * @param {string} [baseDir] - Base directory path (optional, defaults to detecting from caller)
 * @returns {Promise<string|null>} The input data as a string, or null if failed
 */
async function readInput(year, day, baseDir = null) {
    try {
        // If no baseDir provided, try to detect it from the calling file
        if (!baseDir) {
            // Get the directory of the file that called this function
            const callerFile = getCallerFile();
            if (callerFile) {
                baseDir = path.dirname(callerFile);
            } else {
                // Fallback to current working directory
                baseDir = process.cwd();
            }
        }

        // First try to read from local input.txt file
        const inputPath = path.join(baseDir, 'input.txt');
        if (fs.existsSync(inputPath)) {
            console.log('Reading from local file...');
            return fs.readFileSync(inputPath, 'utf8').trim();
        }

        // If no local file, try to fetch from URL
        console.log(`Fetching input for ${year} day ${day} from adventofcode.com...`);
        
        if (!config.AOC_SESSION) {
            console.log('No AOC session token found. Please:');
            console.log('1. Set AOC_SESSION environment variable, or');
            console.log('2. Add your session token to js/utils/config.env, or');
            console.log('3. Create a local input.txt file with your puzzle input');
            return null;
        }
        
        const url = `https://adventofcode.com/${year}/day/${day}/input`;
        
        return new Promise((resolve, reject) => {
            const options = {
                headers: {
                    'Cookie': `session=${config.AOC_SESSION}`,
                    'User-Agent': `github.com/xlysia/aoc by ${config.AOC_EMAIL}`
                }
            };

            https.get(url, options, (res) => {
                let data = '';

                if (res.statusCode !== 200) {
                    console.log(`HTTP ${res.statusCode}: ${res.statusMessage}`);
                    if (res.statusCode === 400) {
                        console.log('Bad request - check your session cookie');
                    } else if (res.statusCode === 404) {
                        console.log('Input not found - check year/day or puzzle may not be released yet');
                    } else if (res.statusCode === 500) {
                        console.log('Server error - try again later');
                    }
                    resolve(null);
                    return;
                }

                res.on('data', (chunk) => {
                    data += chunk;
                });

                res.on('end', () => {
                    if (data && data.trim()) {
                        console.log('Successfully fetched from URL');
                        
                        // Optionally save to local file for future use
                        try {
                            fs.writeFileSync(inputPath, data);
                            console.log('Saved input to local file for future use');
                        } catch (err) {
                            console.log('Could not save to local file:', err.message);
                        }
                        
                        resolve(data);
                    } else {
                        console.log('No data received from URL');
                        resolve(null);
                    }
                });
            }).on('error', (error) => {
                console.error('Error fetching from URL:', error.message);
                resolve(null);
            });
        });
        
    } catch (error) {
        console.error('Error reading input:', error.message);
        return null;
    }
}

/**
 * Get the file path of the calling function (utility to detect caller directory)
 */
function getCallerFile() {
    try {
        const originalFunc = Error.prepareStackTrace;
        let callerfile;
        
        Error.prepareStackTrace = function (err, stack) {
            return stack;
        };
        
        const err = new Error();
        const currentfile = err.stack.shift().getFileName();
        
        while (err.stack.length) {
            callerfile = err.stack.shift().getFileName();
            if (currentfile !== callerfile) break;
        }
        
        Error.prepareStackTrace = originalFunc;
        return callerfile;
    } catch (e) {
        return null;
    }
}

/**
 * Parse input as lines
 * @param {string} input - The input string
 * @returns {string[]} Array of lines
 */
function parseLines(input) {
    return input.split('\n').filter(line => line.trim() !== '');
}

/**
 * Parse input as comma-separated integers
 * @param {string} input - The input string
 * @returns {number[]} Array of integers
 */
function parseCommaSeparatedInts(input) {
    return input.split(',').map(num => parseInt(num.trim()));
}

/**
 * Parse input as space-separated integers
 * @param {string} input - The input string
 * @returns {number[]} Array of integers
 */
function parseSpaceSeparatedInts(input) {
    return input.split(/\s+/).map(num => parseInt(num.trim()));
}

/**
 * Parse input as a grid of characters
 * @param {string} input - The input string
 * @returns {string[][]} 2D array of characters
 */
function parseGrid(input) {
    return input.split('\n').map(line => line.split(''));
}

module.exports = {
    readInput,
    parseLines,
    parseCommaSeparatedInts,
    parseSpaceSeparatedInts,
    parseGrid
};