CC       = g++
CPPFLAGS = -Wall -g
BIN_DIR  = bin
GTEST_LL = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread

all: listtest queuetest scheduling cnfeval

listtest: $(BIN_DIR)/.dirstamp $(BIN_DIR)/llistint.o listtest.cpp
	$(CC) $(CPPFLAGS) $(BIN_DIR)/llistint.o listtest.cpp $(GTEST_LL) -o listtest

$(BIN_DIR)/llistint.o: llistint.h llistint.cpp
	$(CC) $(CPPFLAGS) -c llistint.cpp -o $(BIN_DIR)/llistint.o

queuetest: $(BIN_DIR)/.dirstamp $(BIN_DIR)/queueint.o queuetest.cpp llistint.cpp
	$(CC) $(CPPFLAGS) $(BIN_DIR)/queueint.o queuetest.cpp llistint.cpp $(GTEST_LL) -o queuetest

$(BIN_DIR)/queueint.o: queueint.h queueint.cpp
	$(CC) $(CPPFLAGS) -c queueint.cpp -o $(BIN_DIR)/queueint.o

scheduling: $(BIN_DIR)/.dirstamp $(BIN_DIR)/scheduling.o queueint.cpp llistint.cpp
	$(CC) $(CPPFLAGS) $(BIN_DIR)/scheduling.o queueint.cpp llistint.cpp -o scheduling

$(BIN_DIR)/scheduling.o: scheduling.cpp
	$(CC) $(CPPFLAGS) -c scheduling.cpp -o $(BIN_DIR)/scheduling.o

cnfeval: $(BIN_DIR)/.dirstamp $(BIN_DIR)/cnf.o cnfeval.cpp
	$(CC) $(CPPFLAGS) $(BIN_DIR)/cnf.o cnfeval.cpp -o cnfeval

$(BIN_DIR)/cnf.o: cnf.h cnf.cpp
	$(CC) $(CPPFLAGS) -c cnf.cpp -o $(BIN_DIR)/cnf.o


$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamp

.PHONY: clean tests

tests: $(BIN_DIR)/listtest $(BIN_DIR)/queuetest
	-@$(BIN_DIR)/listtest
	-@$(BIN_DIR)/queuetest
	-@$(BIN_DIR)/scheduling
	-@echo "--- All Tested!---"

clean:
	-@rm -rf $(BIN_DIR)
	-rm listtest
	-rm queuetest
	-rm scheduling
	-rm cnfeval
	-@echo "--- All Clean!---"