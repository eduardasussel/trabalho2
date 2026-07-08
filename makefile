EXEC = ted

CC = gcc
CFLAGS = -std=gnu99 -fstack-protector-all -Wall
LIBS = -lm

BED = ./entrada
BSD = ./saida

SRC = main.c lerGeo.c lerQry.c comandos.c arvore.c forma.c lista.c ordena.c svg.c
OBJ = $(SRC:.c=.o)

all: $(EXEC)

ted: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)
	rm -rf $(BSD)/*

test: $(EXEC)
	@echo "INICIANDO TESTES"
	@mkdir -p $(BSD)
	@for qry in $$(find $(BED) -type f -name "*.qry" | tr -d '\r'); do \
		qry_relativo=$${qry#$(BED)/}; \
		pasta_mae=$$(basename $$(dirname $$qry) | tr -d '\r'); \
		geo_arq="$$pasta_mae.geo"; \
		if [ -f "$(BED)/$$geo_arq" ]; then \
			echo "---------------------------------------------------------"; \
			echo "Executando: $$geo_arq com $$qry_relativo"; \
			./$(EXEC) -e "$(BED)" -f "$$geo_arq" -o "$(BSD)" -q "$$qry_relativo"; \
		else \
			echo "⚠️ Aviso: .geo correspondente não encontrado para $$qry_relativo"; \
		fi \
	done
	@echo "TESTES CONCLUIDOS!"