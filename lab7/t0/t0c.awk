BEGIN {OFS="\t"}
$2 ~ /a/ {print $2,$4}
