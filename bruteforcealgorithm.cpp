// test.cpp - originally written and placed in the public domain by Wei Dai
//            CryptoPP::Test namespace added by JW in February 2017
//            scoped_main added to CryptoPP::Test namespace by JW in July 2017
//            Also see http://github.com/weidai11/cryptopp/issues/447

#define CRYPTOPP_DEFAULT_NO_DLL
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1

#include <iostream>
#include <sstream>
#include <locale>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <math.h>

using namespace std;

std::string EncryptString(const char *plaintext, const char *passPhrase);
std::string DecryptString(const char *ciphertext, const char *passPhrase);


void fuerzaBruta(string TextoACrackear, int KeyMaxLength, int opc) {

	int keynum = 0, keycounter = 0, n, d, numero;
	string TextoPlano, Alfabeto = "abcdefghijklmn\xA4opqrstuvwxyz", check;
	byte Key[24];
	bool Encontrado = false;

	// Si el usuario indica que quiere emplear numeros, anyadimos los numeros al alfabeto.
	if (opc == 1) {
		Alfabeto = Alfabeto + "0123456789";
	}

	// determinamos la longitud del alfabeto y de las posibles llaves
	int Tam_Alfabeto = Alfabeto.length(), PossibleKeys = pow(Tam_Alfabeto, KeyMaxLength);

	// calculamos el numero total de posibles llaves
	for (int i = 1; i <= KeyMaxLength; i++) {
		keynum += pow(Tam_Alfabeto, i);
	}

	cout << "Testing up to " << keynum << " keys with the max length of " << KeyMaxLength;
	cout << ", using the alphabet: " << Alfabeto;

	// comenzamos el timer.
	clock_t start = clock();

	for (int i = 1; i <= KeyMaxLength; i++) {
		n = pow(Tam_Alfabeto, i);
		for (int j = 0; j < n; j++) {
			string llave = "";
			d = j;
			for (int k = 0; k < i; k++) {
				numero = d % Tam_Alfabeto;
				llave = Alfabeto[numero] + llave;
				d /= Tam_Alfabeto;
			}
			keycounter++;
			try {

				//cout << "Key [ " << keycounter << " ] is " << llave << endl;
				TextoPlano = DecryptString(TextoACrackear.c_str(), llave.c_str());
				check = TextoPlano;
				std::cout << "\nDecrypted Plain text: " << TextoPlano << " ... With Key ( " << llave << " ) - number " << keycounter << std::endl;
			}
			catch (const std::exception& e) {
				//cout << "\nDecryption failed with error: " << e.what() << endl;
			}
			if (check.length() > 0) {
				break;
			}
		}
	}

	if (check.length() == 0) {
		cout << endl << "Decryption failed. Unable to find key." << endl;
	}
	clock_t end = clock();
	double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
	double time_taken_ms = time_taken * 1000;
	cout << "Operation took a total of ** " << time_taken << " ** seconds" << endl;
	cout << "Operation took a total of ** " << time_taken_ms << " ** miliseconds" << endl;
	cout << "Amount of keys tested: " << keycounter;

}
