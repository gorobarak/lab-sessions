BEGIN {FS=","; OFS = " | "}
{print $4,$3,$2}