gcc -o app main.c adminChoice.c productCRUD.c userAdminCRUD.c userAuth.c userChoice.c userProduct.c adminPointOfSale.c adminAccounting.c
./app

White \033[0;37m
Black \033[0;30m
Red \033[0;31m
Green \033[0;32m
Yellow \033[0;33m
Blue \033[0;34m
Purple \033[0;35m
Cyan \033[0;36m
White \033[0;37m


void reset () {
  printf("\033[0m");
}
