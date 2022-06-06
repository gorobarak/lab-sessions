BEGIN {FS=","; cnt = 0}
$3 == "bachelor's degree" {cnt++}
END {print "num of students that their parents have bachelor's degree:",cnt}