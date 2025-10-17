# Advent of Code Solutions

This repository contains solutions for Advent of Code challenges in multiple languages.

## C++ Solutions (Original)

### Setup
1. First run bash for the include file:
```bash
bash ./setup.sh
```

2. Build:
```bash
mkdir build
cd build
cmake ..
make -j8
```

3. Run:
```bash
build/aoc YEAR DAY
```

## JavaScript Solutions (New)

### Quick Setup

1. **Configure your AOC session token** in `js/utils/config.env`:
```env
AOC_SESSION=your_session_token_here
AOC_EMAIL=your-email@example.com
```

2. **Get your session token**:
   - Go to [adventofcode.com](https://adventofcode.com) and log in
   - Open Developer Tools (F12) → Network tab
   - Visit any puzzle input page
   - Find the request and copy the `session=` value from the Cookie header

3. **Run a solution**:
```bash
cd 2019/day2
node main.js
```

### JavaScript Utilities

The repository includes a utility module at `js/utils/readInput.js` that:
- ✅ Automatically fetches puzzle inputs from adventofcode.com
- ✅ Caches inputs locally for faster subsequent runs  
- ✅ Provides parsing helpers for common input formats
- ✅ Falls back to local files if network is unavailable

#### Usage Example
```javascript
const { readInput, parseCommaSeparatedInts } = require('../../js/utils/readInput');

async function main() {
    const input = await readInput(2019, 2);
    const numbers = parseCommaSeparatedInts(input);
    // Solve the puzzle...
}

main();
```

#### Available Parsing Functions
- `parseLines(input)` - Split into non-empty lines
- `parseCommaSeparatedInts(input)` - Parse comma-separated integers
- `parseSpaceSeparatedInts(input)` - Parse space-separated integers  
- `parseGrid(input)` - Parse into 2D character array

### How Input Fetching Works

1. Checks for local `input.txt` file first
2. If not found, fetches from adventofcode.com using your session token
3. Automatically saves fetched input for future use
4. Provides helpful error messages for common issues

### Security

**Important**: Never commit your session token! The `config.env` file is included as a template - update it with your real token locally.

### Troubleshooting

- **"No AOC session token found"**: Add your session token to `config.env`
- **"HTTP 400 Bad Request"**: Your session token is invalid/expired
- **"HTTP 404 Not Found"**: Check year/day numbers or puzzle may not be released yet

## Project Structure

```
aoc/
├── js/utils/          # JavaScript utilities
├── 2019/day1/         # JavaScript solutions
├── 2015/day1/         # C++ solutions  
├── template/          # Solution templates
├── utils/             # C++ utilities
└── CMakeLists.txt     # C++ build config
```

