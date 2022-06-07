#3a
# BEGIN {FS=","}
# /spring/ {print $2,"---",$3,"---",$4} 

#3b
# BEGIN {FS=","; counter=0}
# /f[au]n/{counter++}
# END {print "The number of poem that have fun or fan is : ",counter}

#3c
# BEGIN {FS=","}
# $2 ~ /happy/ {print $2,"---",$3,"---",$4}