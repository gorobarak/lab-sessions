BEGIN {FS=",";OFS = "\t";w = 0; m=0;}
$1 == "male" {m++}
$1 == "female" {w++}
END {print "Num of men: ",m,"\nNum of women: ", w}