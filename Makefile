OBJFILES = main.o ast.o tokenizer.o

%.o: %.cpp
	gcc -o $@ $^ -c 

all: $(OBJFILES)
	gcc -o main $(OBJFILES) -lm -g

clean:
	-rm $(OBJFILES)
	-rm main