#!/bin/bash 
Directory=$1
option=$2

flag=0     # if flag equals 1 then copy files othereise just rename them.
if [ "$option" = "-c" ] || [ "$option" = "--copy" ]; then
    flag=1
fi

if [ -d "$Directory" ]; then    # if the directory is valid 
    echo "directory submitted successfully!"
    date="`date +%Y-%m-%d`_"    # to type ` ` symbol : hold alt + 96
    if [ $flag == "1" ]; then
         for file in $Directory/*
         do
            filename=$(basename "$file")
            extension=${filename##*.}

            cp "$file" "$Directory/$date$filename"
            echo "name: $filename  type :.$extension -> making copy: $date$filename" 
        done
    else            # if the directory is not valid
        for file in $Directory/*            
        do
            filename=$(basename "$file")
            extension=${filename##*.}  

            mv "$file" "$Directory/$date$filename"
            echo "name: $filename type :.$extension -> changing name to: $date$filename" 
        done
    fi
else
   echo "No such directory"
fi