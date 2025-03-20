CFILES = main.c ast.c tokenizer.c

# %.o: %.cpp
# 	gcc -o $@ $^ -c -g

all: $(CFILES)
	gcc -o main $(CFILES) -g -lm

clean:
	-rm main