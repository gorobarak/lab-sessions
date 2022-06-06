BEGIN {OFS="\t"; cnt = 0}
{if ($3 ~ /English/) cnt++}
END {print "Count =",cnt}
