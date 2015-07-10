
here:
	     gcc -o tcp_server_c main.c srv_tcp.c gui.c \
		   kernellist.c sql.c -lpthread -lsqlite3 -ljson
clean:
	    $(RM) -rf tcp_server_c .*.*.swp
#../$(BIN_DIR)/server:server.c
#		  $(CC) $(WALL) -o $@ $^
