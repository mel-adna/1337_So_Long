MANDATORY = Mandatory
BONUS = Bonus

.PHONY: all mandatory bonus clean fclean re

all: 
	@clear
	@echo "\033[1;34m=====================================\033[0m"
	@echo "\033[1;32m          Building so_long          \033[0m"
	@echo "\033[1;34m=====================================\033[0m"
	@echo "\033[1;36m🔄 Compiling Mandatory...\033[0m"
	@$(MAKE) -C $(MANDATORY)
	@echo "\033[1;36m🔄 Compiling Bonus...\033[0m"
	@$(MAKE) -C $(BONUS)
	@echo "\033[1;32m✅ Make Done!\033[0m"

mandatory:
	@echo "\033[1;36m🔄 Compiling Mandatory...\033[0m"
	@$(MAKE) -C $(MANDATORY)

bonus:
	@echo "\033[1;36m🔄 Compiling Bonus...\033[0m"
	@$(MAKE) -C $(BONUS)

clean:
	@clear
	@echo "\033[1;34m=====================================\033[0m"
	@echo "\033[1;32m          Cleaning so_long          \033[0m"
	@echo "\033[1;34m=====================================\033[0m"
	@echo "\033[1;36m🔄 Compiling Cleaning...\033[0m"
	@echo "\033[1;33m🧹 Cleaning...\033[0m"
	@$(MAKE) clean -C $(MANDATORY)
	@$(MAKE) clean -C $(BONUS)
	@echo "\033[1;32m✅ Clean Done!\033[0m"

fclean:
	@clear
	@echo "\033[1;34m=====================================\033[0m"
	@echo "\033[1;32m        Full Cleaning so_long        \033[0m"
	@echo "\033[1;34m=====================================\033[0m"
	@echo "\033[1;36m🔄 Compiling Full Cleaning...\033[0m"
	@echo "\033[1;31m🔥 Full Clean...\033[0m"
	@$(MAKE) fclean -C $(MANDATORY)
	@$(MAKE) fclean -C $(BONUS)
	@echo "\033[1;32m✅ Full Clean Done!\033[0m"

re: fclean all

