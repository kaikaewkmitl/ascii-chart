# ASCII Chart Generator

Counts ASCII characters from files provided then generates a chart displaying counts of each character

KMITL's C-programming project by Mahnun Saratunti (64011456)

## Preview

![preview](./images/preview.png)

## Install

### Using Cmake only

```
git clone https://github.com/kaikaewkmitl/ascii-chart.git
cd ascii-chart
mkdir build && cd build
cmake .. && cmake --build .
cd ..
```

### Using Makefile and Cmake

```
git clone https://github.com/kaikaewkmitl/ascii-chart.git
cd ascii-chart
make build
```

## Requirement

Requires global environment COLUMNS(terminal's width) to be set

For Mac, can be done by:

```
export COLUMNS
```

## Run

```
./ascii-chart [-f files...] [--asc]
```

Without any flags the program would run in default mode, with messages prompting for files. With ```-f``` flag provided and files, program would skip the files prompting process and generate a chart right away. The chart is ordered in descending order by default, user can change the ordering by providing the ```--asc``` flag.

## Example

### Input

This example simply reads a text file 'file.txt' with content 'Hello World!' inside. Then displays chart in ascending fashion with ```--asc``` flag

```
echo 'Hello World!' > file.txt && ./ascii-chart -f file.txt --asc
```

### Output

![example](./images/example.png)
