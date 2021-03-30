openssl genrsa -out private-keyVM2.pem 2048
openssl rsa -in private-keyVM2.pem -pubout -out public-keyVM2.pem
openssl req -new -x509 -key private-keyVM2.pem -out certVM2.pem -days 360
openssl pkcs12 -export -in certVM2.pem -inkey private-keyVM2.pem  -out certVM2.p12 -name certVM2
