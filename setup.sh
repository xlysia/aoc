HEADER=all_headers.h
echo "#ifndef __ALL_HEADERS__" > $HEADER
echo "#define __ALL_HEADERS__" >> $HEADER
for file in 2015/*/*.h
do
    echo "#include <$file>" >> $HEADER
done
echo "#endif" >> $HEADER