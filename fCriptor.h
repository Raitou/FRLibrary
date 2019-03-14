class fCriptor{
	public:
		void encrypt(std::string &line, std::string &salt){
			getSalt(salt);
			for(int i = 0; line.length() > i; i++){
				line[i]+=key;
			}
			key = 0;
		}
		void decrypt(std::string &line, std::string &salt){
			getSalt(salt);
			for(int i = 0; line.length() > i; i++){
				line[i]-=key;
			}
			key = 0;
		}
	private:
		void getSalt(std::string &salt){
			for(int i = 0; salt.length() > i; i++){
				key+=(int)salt[i];
			}
		}
		int key = 0;
};
