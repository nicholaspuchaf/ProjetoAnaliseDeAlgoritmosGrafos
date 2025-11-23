# Compilador
CXX = g++
CXXFLAGS = -std=c++17 -O2

# Executável
TARGET = a.out

# Arquivos de teste (1..10)
TESTS = $(shell seq -w 1 10)

all: $(TARGET)

$(TARGET): dialDijkistra.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

dijkistraC : dijkstra.cpp
	$(CXX) $(CXXFLAGS) $< -o dijkstra

dialDijkistraC : dialDijkistra.cpp
	$(CXX) $(CXXFLAGS) $< -o dialDijkistra

biDijkstraC : biDijkstra.cpp
	$(CXX) $(CXXFLAGS) $< -o biDijkstra

biDialDijkstraC : biDialDijkstra.cpp
	$(CXX) $(CXXFLAGS) $< -o biDialDijkstra


# Regra para rodar TODOS os testes
dijkistra: dijkistraC
	@for i in $(TESTS); do \
		echo "== Teste $$i =="; \
		./dijkstra < input/arq$$i.in > temp$$i.out; \
		if diff -q temp$$i.out output/arq$$i.out > /dev/null; then \
			echo "OK"; \
			rm temp$$i.out; \
		else \
			echo "ERRO no teste $$i!"; \
		fi; \
	done
	@echo "----------------------"
	@echo "TODOS OS TESTES PASSARAM!"

dialDijkistra: dialDijkistraC
	@for i in $(TESTS); do \
		echo "== Teste $$i =="; \
		./dialDijkistra < input/arq$$i.in > temp$$i.out; \
		if diff -q temp$$i.out outputF/arq$$i.out > /dev/null; then \
			echo "OK"; \
			rm temp$$i.out; \
		else \
			echo "ERRO no teste $$i!"; \
		fi; \
	done
	@echo "----------------------"
	@echo "TODOS OS TESTES PASSARAM!"

biDijkstra: biDijkstraC
	@for i in $(TESTS); do \
		echo "== Teste $$i =="; \
		./biDijkstra < input/arq$$i.in > temp$$i.out; \
		if diff -q temp$$i.out output/arq$$i.out > /dev/null; then \
			echo "OK"; \
			rm temp$$i.out; \
		else \
			echo "ERRO no teste $$i!"; \
		fi; \
	done
	@echo "----------------------"
	@echo "TODOS OS TESTES PASSARAM!"

biDialDijkistra: biDialDijkstraC
	@for i in $(TESTS); do \
		echo "== Teste $$i =="; \
		./biDialDijkstra < input/arq$$i.in > temp$$i.out; \
		if diff -q temp$$i.out outputF/arq$$i.out > /dev/null; then \
			echo "OK"; \
			rm temp$$i.out; \
		else \
			echo "ERRO no teste $$i!"; \
		fi; \
	done
	@echo "----------------------"
	@echo "TODOS OS TESTES PASSARAM!"


timerDijkstra: dijkistraC
	@echo "---Dijkistra---------"
	@for i in $(TESTS); do \
		echo "== Teste $$i =="; \
		./dijkstra < input/arq$$i.in; \
		echo ""; \
	done
	@echo "----------------------"
	@echo "TODOS OS TESTES FORAM RODADOS!"

timerDialDijkstra: dialDijkistraC
	@echo "---Dial Dijkistra---------"
	@for i in $(TESTS); do \
		echo "== Teste $$i =="; \
		./dialDijkistra < input/arq$$i.in; \
		echo ""; \
	done
	@echo "----------------------"
	@echo "TODOS OS TESTES FORAM RODADOS!"

timerBiDijkstra: biDijkstraC
	@echo "---Bi Dijkstra---------"
	@for i in $(TESTS); do \
		echo "== Teste $$i =="; \
		./biDijkstra < input/arq$$i.in; \
		echo ""; \
	done
	@echo "----------------------"
	@echo "TODOS OS TESTES FORAM RODADOS!"	

timerBiDialDijkstra: biDialDijkstraC
	@echo "---Bi Dial Dijkistra---------"
	@for i in $(TESTS); do \
		echo "== Teste $$i =="; \
		./biDialDijkstra < input/arq$$i.in; \
		echo ""; \
	done
	@echo "----------------------"
	@echo "TODOS OS TESTES FORAM RODADOS!"

