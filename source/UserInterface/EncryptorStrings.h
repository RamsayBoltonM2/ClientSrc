#include "stdafx.h"

std::string FromHex(const std::string& in) {
	std::string output;
	if ((in.length() % 2) != 0) {
		FILE *f=fopen("HackShield.Config.Error.txt", "w");
		fputs("[HackShield] Error while decrypting this text: ", f);
		fputs(in.c_str(), f);
		fputs("\n", f);
		fclose(f);
		exit(-1);
		return "";
	}
	size_t cnt = in.length() / 2;
	for (size_t i = 0; cnt > i; ++i) {
		unsigned long int s = 0;
		std::stringstream ss;
		ss << std::hex << in.substr(i * 2, 2);
		ss >> s;
		output.push_back(static_cast<unsigned char>(s));
	}
	return output;
}

std::string UltimateCipher(std::string Str) {
	char Key[3] = { 'A', 'B', 'C' };
	std::string Encrypted = Str;
	for (unsigned int i = 0; i<Str.size(); i++) Encrypted[i] = Str[i] ^ Key[i % (sizeof(Key) / sizeof(char))];
	return Encrypted;
}

std::string UltimateDecrypt(std::string MyString) {
	return UltimateCipher(FromHex(MyString));
}
