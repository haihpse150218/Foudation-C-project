#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>
#include<windows.h>
#define BIT 32
/*
Function store input and return how many char
@arg: char: array buffer store list char be inputed
@return: int: count_char
*/
int count_bit_input(char *buffer){
	char c;
	int i = 0;
	for(int i = 0 ; i < BIT; i++){
		buffer[i] = '!';
	}
	do{
		c = getchar();
		if(c != 10){
			buffer[i] = c;
		}
		i++;
	}while(c != 10);
	int count_bit = i - 1;
	return count_bit;
}

bool is_wrong_condition(char buffer[], int count_bit){
	bool check;
	check = false;
	for(int i = 0; i < count_bit; i++){
		if(buffer[i] != '0' && buffer[i] != '1'){
			if(i == 0 && (buffer[i] == '+' || buffer[i] == '-')){
				check = false;
			}
			else{
				printf("This is NOT binary number. ");
				check = true;
				break;
			}	
		}		
	}
	if(buffer[0] == '+' || buffer[0] == '-'){
		if(count_bit > BIT + 1){
			printf("Overflow. " );
			check = true;
		}
		else if(count_bit == BIT + 1){
			if(buffer[1] == '1'){
				printf("Overflow. " );
				check = true;
			}
		}	
	}
	else{
		if(count_bit > BIT){
			printf("Overflow. ");
			check = true;
		}
	}
	
	if(check == true){
		printf("\nEnter again: ");
	}
	return check;
}

void input_op(char *op){
	scanf("%c", op);
	fflush(stdin);
}
bool is_wrong_op(char op){
	bool check = false;
	if(op != '+' && op != '-'){
		printf("Entern again operator ('+', '-'): ");
		check = true;
	}
	return check;
}

void filt_value(char* binary_num, char buffer[], int count_bit){
	int index = 0;
//	default 32bit
	for(int i = 0; i < BIT; i++){
		binary_num[i] = '0';
	}
//	fill sign
	if(buffer[0] == '-'){
		binary_num[0] = '1';
	}else{
		binary_num[0] = '0';
	}
//fill value
	// su ly 32 bit + co dau
	if(buffer[0] == '-'|| buffer[0] == '+'){
		index = 1;
	}
	
	if(count_bit == BIT + 1){
		for(int i = 2; i < BIT + 1; i++){
			binary_num[i-1] = buffer[i];
		}
	}
	else{
		for(int i = count_bit - 1; i >= index; i --){
			binary_num[BIT - count_bit + i] = buffer[i];
		}
	}
}

//processing
void change_sign(char *sign){
	if(*sign == '0'){
		*sign = '1';
	}else{
		*sign = '0';
	}
}

bool XOR(char a, char b){
	bool check;
	if(a == b){
		check = false;
	}else check = true;
	return check;
}

void twos_complement(char * list_binary){
	for(int i = BIT - 1; i > 0; i--){
		if(*(list_binary + i) == '1'){
			for(int j = i - 1; j > 0; j--){
				if(*(list_binary + j) == '1'){
					*(list_binary + j) = '0';
				}
				else{
					*(list_binary + j) = '1';
				}
			}
			break;
		}
	}
}

bool adding(char num1[], char num2[], char *sum){
	bool is_overflow = false;
	char carry = '0';
	for(int i = BIT - 1; i > 0; i--){
		if(num1[i] == num2[i]){
			if(num1[i] == '0'){
				*(sum + i) = carry;
				carry = '0';
			}
			else{
				*(sum + i) = carry;
				carry = '1';
			}			
		}
		else{
			if(carry == '0'){
				*(sum + i) = '1';
				carry = '0';
			}
			else{
				*(sum + i) = '0';
				carry = '1';
			}
		}
		
	}
	if(carry == '1'){
		is_overflow = true;
	}
	return is_overflow;
}

bool is_subtract(char op){
	bool check = false;
	if(op == '-'){
		check = true;
	}
	return check;
}	

bool is_number_0(char arr[]){
	bool check = true;
	for(int i = 1; i < 32 ; i++){
		if(arr[i] != '0'){
			check = false;
			break;
		}
	}
	return check;
}

int convert_bin_to_dec(char arr[]){
	int dec_num = 0;
	for(int i = BIT; i > 0; i--){
		if(arr[i] == '1'){
			dec_num += pow(2, BIT - 1 - i);
		}
	}
	if(arr[0] == '1'){
		dec_num = -dec_num;
	}
	return dec_num;
}
void manual(){
	printf("\t\t\t!==========Manual==========!\n");
	printf("\tFormat binary: 1 bit sign(1(-) or 0(+)) and 31 bit (Magnitude):\n");
	printf("\tYou can input less than 32 bit follow this way:\n");
	printf("\tsign format input: '+' or '-', if none default '+'\n");
	printf("\tMagnitude format input: 1 or 0, and <= 32 bit.\n");
	printf("\t\t\t!==========================!\n");
}

void dishplay_input(char a[], int count_bit){
	printf("\t");
	for(int i = 0; i < BIT; i++){
			printf("%c", a[i]);
		}
	printf("\n");	
}

int main(){
	char binary_num_A[BIT], buffer_1[BIT + 2];
	char binary_num_B[BIT], buffer_2[BIT + 2];
	char op;
	int count_bit_1, count_bit_2;
	manual();
	printf("Enter a binary number A (A <=32bit):\n");
	do{
		count_bit_1 = count_bit_input(buffer_1);
	}while(is_wrong_condition(buffer_1, count_bit_1));

	
	printf("Enter a operator ('+', '-'): ");
	do{
		input_op(&op);
	}while(is_wrong_op(op));
	
	printf("Enter a binary number B (B <=32bit):\n");
	do{
		count_bit_2 = count_bit_input(buffer_2);
	}while(is_wrong_condition(buffer_2, count_bit_2));
	
	system("cls");
	system("color 2");
	printf("\t==Addition and subtraction of integers in sign-and-magnitude format==\n");
	filt_value(binary_num_A, buffer_1, count_bit_1);
	dishplay_input(binary_num_A, count_bit_1);
	printf("\t%c\n", op);
	filt_value(binary_num_B, buffer_2, count_bit_2);
	dishplay_input(binary_num_B, count_bit_2);
//processing
	char Rm[BIT];
	char As = binary_num_A[0];
	char Bs = binary_num_B[0];
	bool is_overflow = false;
	bool is_over_32bit = false;
	if(is_subtract(op) && !is_number_0(binary_num_B)){
		change_sign(&Bs);		
	}
//	raise: 1 + (-0) and 1 - 0 is wrong.
	else if(is_number_0(binary_num_B)){
		Bs = As;
	}
// it not follow roadmap !!!
	if(XOR(As, Bs)){ 
		twos_complement(binary_num_B);
		is_overflow = adding(binary_num_A, binary_num_B, Rm);
		if(is_overflow){
			Rm[0] = As;
		}
		else{
			twos_complement(Rm);
			Rm[0] = Bs;
		}
	}
	else{
		is_overflow = adding(binary_num_A, binary_num_B, Rm);
		if(is_overflow){
			is_over_32bit = true;	
		}
		else Rm[0] = As;
	}
	
	
	
	if(is_over_32bit){
		printf("Overflow!");
	}
	else{
		printf("Result: ================================\nBin:\t");
		for(int i = 0; i < BIT; i++){
			printf("%c",Rm[i]);
		}
		printf("\nDec: %d", convert_bin_to_dec(Rm));
	}
}
