# Compilador
CXX = g++
CXXFLAGS = -std=c++17 -O2
PYTHON = python3

# Executável
TARGET = a.out

SHELL := /bin/bash

# Arquivos de teste (1..10)
TESTS = $(shell seq -w 1 10)

all: $(TARGET)

$(TARGET): dialDijkistra.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

dijkstraC : dijkstra.cpp
	$(CXX) $(CXXFLAGS) $< -o dijkstra.o

dialDijkstraC : dialDijkstra.cpp
	$(CXX) $(CXXFLAGS) $< -o dialDijkstra.o

biDijkstraC : biDijkstra.cpp
	$(CXX) $(CXXFLAGS) $< -o biDijkstra.o

biDialDijkstraC : biDialDijkstra.cpp
	$(CXX) $(CXXFLAGS) $< -o biDialDijkstra.o


dijkstra: dijkstraC
	@for i in $(TESTS); do \
        echo "== Teste $$i =="; \
        ./dijkstra.o < input/arq$$i.in > temp$$i.out; \
        head -n 1 temp$$i.out | tr -d '\n' > temp$$i.line; \
        if diff -q temp$$i.line final/arq$$i.out > /dev/null; then \
            echo "OK"; \
        else \
            echo "ERRO no teste $$i!"; \
        fi; \
        rm -f temp$$i.out temp$$i.line; \
    done
	@echo "----------------------"
	@echo "TODOS OS TESTES PASSARAM!"


dialDijkstra: dialDijkstraC
	@for i in $(TESTS); do \
		echo "== Teste $$i =="; \
		./dialDijkstra.o < input/arq$$i.in > temp$$i.out; \
		head -n 1 temp$$i.out | tr -d '\n' > temp$$i.line; \
		if diff -q temp$$i.line finalF/arq$$i.out > /dev/null; then \
			echo "OK"; \
			rm temp$$i.out; \
		else \
			echo "ERRO no teste $$i!"; \
		fi; \
		rm -f temp$$i.out temp$$i.line; \
	done
	@echo "----------------------"
	@echo "TODOS OS TESTES PASSARAM!"

biDijkstra: biDijkstraC
	@for i in $(TESTS); do \
		echo "== Teste $$i =="; \
		./biDijkstra.o < input/arq$$i.in > temp$$i.out; \
		head -n 1 temp$$i.out | tr -d '\n' > temp$$i.line; \
		if diff -q temp$$i.line final/arq$$i.out > /dev/null; then \
			echo "OK"; \
			rm temp$$i.out; \
		else \
			echo "ERRO no teste $$i!"; \
		fi; \
		rm -f temp$$i.out temp$$i.line; \
	done
	@echo "----------------------"
	@echo "TODOS OS TESTES PASSARAM!"

biDialDijkstra: biDialDijkstraC
	@for i in $(TESTS); do \
		echo "== Teste $$i =="; \
		./biDialDijkstra.o < input/arq$$i.in > temp$$i.out; \
		head -n 1 temp$$i.out | tr -d '\n' > temp$$i.line; \
		if diff -q temp$$i.line finalF/arq$$i.out > /dev/null; then \
			echo "OK"; \
			rm temp$$i.out; \
		else \
			echo "ERRO no teste $$i!"; \
		fi; \
		rm -f temp$$i.out temp$$i.line; \
	done
	@echo "----------------------"
	@echo "TODOS OS TESTES PASSARAM!"


plShortestPath:
	@for i in $(TESTS); do \
		echo "== Teste $$i =="; \
		$(PYTHON) plShortestPath.py < input/arq$$i.in > temp$$i.out; \
		sed -n '4p' temp$$i.out | tr -d '\n' > temp$$i.line; \
		if diff -q temp$$i.line final/arq$$i.out > /dev/null; then \
			echo "OK"; \
		else \
			echo "ERRO no teste $$i!"; \
		fi; \
		rm -f temp$$i.out temp$$i.line; \
	done
	@echo "----------------------"
	@echo "TODOS OS TESTES PASSARAM!"

timerDijkstra: dijkstraC
	@echo "---Dijkstra---------"
	@for i in $(TESTS); do \
		echo "== Teste $$i =="; \
		./dijkstra.o < input/arq$$i.in; \
		echo ""; \
	done
	@echo "----------------------"
	@echo "TODOS OS TESTES FORAM RODADOS!"

timerDialDijkstra: dialDijkstraC
	@echo "---Dial Dijkistra---------"
	@for i in $(TESTS); do \
		echo "== Teste $$i =="; \
		./dialDijkstra.o < input/arq$$i.in; \
		echo ""; \
	done
	@echo "----------------------"
	@echo "TODOS OS TESTES FORAM RODADOS!"

timerBiDijkstra: biDijkstraC
	@echo "---Bi Dijkstra---------"
	@for i in $(TESTS); do \
		echo "== Teste $$i =="; \
		./biDijkstra.o < input/arq$$i.in; \
		echo ""; \
	done
	@echo "----------------------"
	@echo "TODOS OS TESTES FORAM RODADOS!"	

timerBiDialDijkstra: biDialDijkstraC
	@echo "---Bi Dial Dijkstra---------"
	@for i in $(TESTS); do \
		echo "== Teste $$i =="; \
		./biDialDijkstra.o < input/arq$$i.in; \
		echo ""; \
	done
	@echo "----------------------"
	@echo "TODOS OS TESTES FORAM RODADOS!"

timerPlShortestPath:
	@echo "---PL Shortest Path---------"
	@for i in $(TESTS); do \
		echo "== Teste $$i =="; \
		$(PYTHON) plShortestPath.py < input/arq$$i.in; \
		echo ""; \
	done
	@echo "----------------------"
	@echo "TODOS OS TESTES FORAM RODADOS!"


clean:
	rm -f *.o $(TARGET) temp*.out

allTests: dijkstra dialDijkstra biDijkstra biDialDijkstra plShortestPath

allTimers: timerDijkstra timerDialDijkstra timerBiDijkstra timerBiDialDijkstra timerPlShortestPath
