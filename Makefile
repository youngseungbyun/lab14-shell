PROJ_DIR = $(shell pwd)
SRC_DIR = $(PROJ_DIR)/src
INC_DIR = $(PROJ_DIR)/include
OBJ_DIR = $(PROJ_DIR)/obj
BIN_DIR = $(PROJ_DIR)/bin
HEADERS = $(INC_DIR)/ls_commend.h $(INC_DIR)/cat_commend.h

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) | $(OBJ_DIR)
	gcc -c -o $@ $< -I$(INC_DIR)

$(BIN_DIR)/myshell: $(OBJ_DIR)/myshell.o $(OBJ_DIR)/ls_commend.o $(OBJ_DIR)/cat_commend.o | $(BIN_DIR)
	gcc -o $@ $^ -I$(INC_DIR)

$(BIN_DIR):
	mkdir -p $@

$(OBJ_DIR):
	mkdir -p $@

#임시파일만 지움
clean:
	rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/myshell 

#디렉토리까지 지움
distclean:
	rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/myshell 
	rm -rf $(OBJ_DIR) $(BIN_DIR)