##JOI para C++ [MVP]
<br>

> Um simples* header-only* validador de *inputs* feito inspirado no [JOI](https://github.com/hapijs/joi "JOI") do NodeJS. 
Foi utilizado o **Builder Design Pattern** para organização do projeto.

O validador trabalha somente na validação de variáveis, mas futuramente pretendo implementar validação de classes/estruturas para se aproximar mais de como é o **JOI** no *javascript*. 
<br>
#####Validação de String 

	JoiString schema = JoiString::build().alphanum().maximum(32).required();
	JoiResult result = JoiString::validate(input, &schema);

*input* não pode ser vazio, deve ter no máximo 32 caracteres e só pode ser alfanumérico.

Para verificar se houve algum erro, basta consultar o resultado do *validate*

	if(result.error())
		cout << result.description() << endl;

<br>
------------



#####Validação de um Inteiro 

	JoiNumber schema = JoiNumber::build().minimum(50).maximum(100);
	JoiResult result = JoiNumber::validate(value, &schema);

*value* deve atender ao intervalo [50, 100]

Para verificar se houve algum erro, basta consultar o resultado do *validate*

	if(result.error())
		cout << result.description() << endl;

<br>
**Bye bye ;~)**

