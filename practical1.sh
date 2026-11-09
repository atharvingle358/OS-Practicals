
#!/bin/bash

echo "Enter a number:"
read n

if [ "$n" -gt 0 ]; then
    echo "Positive number"
elif [ "$n" -lt 0 ]; then
    echo "Negative number"
else
    echo "Zero"
fi
