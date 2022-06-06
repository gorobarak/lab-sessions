BEGIN {FS=",";OFS = "\t";cnt = 0; print "Success Students List:"}
$6 >= 80 && $7 >= 80 && $8 >= 80 && NR > 1 {print $1,$2,$3,$4,$5,$6,$6,$7,$8; cnt++}
END {print "Num of success students:",cnt}