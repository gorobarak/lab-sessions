BEGIN {FS=","}
$2 >= 1970 && NR > 1 {printf "Actor name:%s\nMovie name:%s\n---------------\n",$4,$5}