SRC=data_race_example.c
BIN=data_race_example

all:
	gcc -o $(BIN) $(SRC)

clean:
	@rm -f $(BIN)