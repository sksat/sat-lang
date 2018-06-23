TARGET	= satc
OBJS	= main.o source.o tokenizer.o

CXX		= clang++
CXXFLAGS= -std=c++1z

%.o: %.cc
	$(CXX) -c $< $(CXXFLAGS) -o $@

default:
	make $(TARGET)

run: $(TARGET)
	./$<

clean:
	rm -rf $(TARGET)
	rm -rf *.o

$(TARGET): $(OBJS) *.hpp
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)
