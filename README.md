# Embarcatech_Temporizadores
Repositório criado para a tarefas de Microcontroladores - Temporizador Periódico e Temporizador de disparo único (One-Shot)

Desenvolvedor:

*Eder Renato da Silva Cardoso Casar*

# Instruções de compilação

Para compilar o código, são necessárias as seguintes extensões: 

*Plataforma de Desenvolvimento BitDogLab v6.3*

*Cmake*

*Wokwi Simulator*

*Raspberry Pi Pico*

Abra o Visual Studio Code, vá na extensão Raspberry Pi Pico, e vá em importar projeto, escolha a pasta do projeto
que deseja testar (Temporizador Periodico ou Temporizador One-Shot)
Após isso, pode dar build no projeto pelo CMake. A partir daí, abra o arquivo 
diagram.json e clique no botão verde para iniciar a simulação, caso queira verificar antes de aplicar na placa.

Após isso, basta conectar a BitDogLab em modo BOOTSEL e dar run.

No Temporizador Periódico, vai funcionar sem necessárias ações do usuário, nele será aplicado um algoritmo de 
semáforo, onde o farol vermelho(led vermelho) iniciará ativo, e a cada 3 segundos o led ativo desligará e outro acenderá
seguindo a ordem: Vermelho-Verde-Amarelo. Na placa BitDogLab, acenderá o led azul ao invés de amarelo.

No Temporizador One-Shot, o usuário apertará o botão A ligado a GPIO 5 da placa, e então todos os leds acenderão, após 3
segundos, o led vermelho apagará, depois de outros 3 segundos o led azul apagará, e por fim o led verde apagará. E então estará
disponível para que o usuário aperte o botão novamente.
