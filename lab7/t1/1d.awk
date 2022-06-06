BEGIN {FS=","}
NR >= 50 && NR <= 70 {print $5}