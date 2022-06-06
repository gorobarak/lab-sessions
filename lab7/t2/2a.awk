BEGIN {FS=","}
NR > 1 && $4 == "standard" {print  ($6 + $7 + $8)/3 }