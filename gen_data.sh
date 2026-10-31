#!/bin/sh
# Run once:  sh gen_data.sh   -> creates every input file the programs need
awk 'BEGIN{for(i=1;i<=400;i++) printf "%d ", i*10; print ""}' > inAsce.dat
awk 'BEGIN{for(i=400;i>=1;i--) printf "%d ", i*10; print ""}' > inDesc.dat
awk 'BEGIN{srand(7); for(i=1;i<=400;i++) printf "%d ", int(rand()*5000)+1; print ""}' > inRand.dat
echo "30 75 2564 1 255 1023 65535 7 100 999 4096 12" > inDec.dat
awk 'BEGIN{srand(3); for(i=1;i<=20;i++) printf "%d %d\n", int(rand()*990)+10, int(rand()*990)+10}' > inGcd.dat
echo "10 40 35 47 68 22 40 10 98 10 50 35 68 40 10" > inArr.dat
cat > inPerson.dat <<'EOT'
0 Adarsh Hota 39 77 231
1 Levi Maier 56 77 129
2 Priya Kumari 63 78 240
3 Dorothy Helton 47 72 229
4 Florence Smith 24 75 171
5 Erica Anyan 38 73 102
6 Norma Webster 23 75 145
EOT
cat > inUnAdjMat.dat <<'EOT'
0 4 0 0 0 0 0 8 0
4 0 8 0 0 0 0 11 0
0 8 0 7 0 4 0 0 2
0 0 7 0 9 14 0 0 0
0 0 0 9 0 10 0 0 0
0 0 4 14 10 0 2 0 0
0 0 0 0 0 2 0 1 6
8 11 0 0 0 0 1 0 7
0 0 2 0 0 0 6 7 0
EOT
# NOTE: manual prints row 4 as "3 0 9 0 2" (typo). Correct matrix for the sample output is below.
cat > inDiAdjMat1.dat <<'EOT'
0 10 0 5 0
0 0 1 2 0
0 0 0 0 4
0 3 9 0 2
7 0 6 0 0
EOT
cat > inDiAdjMat2.dat <<'EOT'
0 3 8 0 -4
0 0 0 1 7
0 4 0 0 0
2 0 -5 0 0
0 0 0 6 0
EOT
cat > kruskal_in.txt <<'EOT'
9 14
1 2 4
1 8 8
2 3 8
2 8 11
3 4 7
3 6 4
3 9 2
4 5 9
4 6 14
5 6 10
6 7 2
7 8 1
7 9 6
8 9 7
EOT
echo "data files generated"
