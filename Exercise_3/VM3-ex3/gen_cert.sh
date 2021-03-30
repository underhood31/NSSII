openssl genrsa -out private-keyVM3.pem 2048
openssl rsa -in private-keyVM3.pem -pubout -out public-keyVM3.pem
openssl req -new -x509 -key private-keyVM3.pem -out certVM3.pem -days 360
openssl pkcs12 -export -in certVM3.pem -inkey private-keyVM3.pem  -out certVM3.p12 -name certVM3
