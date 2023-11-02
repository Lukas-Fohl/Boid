gcc -o ../build/main.o main.c -O2 -std=c99 -lm
echo "comp done"
time ../build/main.o
rm ../build/main.o