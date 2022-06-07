#3a
# BEGIN {FS=","}
# /spring/ {print $2,"---",$3,"---",$4} 
check
#3b
# BEGIN {FS=","; counter=0}
# /fun/ || /fan/{counter++}
# END {print "The number of poem that have fun or fan is : ",counter}

#3c
# BEGIN {FS=","}
# $2 ~ /happy/ {print $2,"---",$3,"---",$4}