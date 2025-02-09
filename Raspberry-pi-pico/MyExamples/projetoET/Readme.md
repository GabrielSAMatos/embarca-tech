# Projeto EmbarcaTech

## Automação de oxigênio e pH em ambiente de criação aquática 

### Apresentação do projeto 

O projeto se trata de uma simulação tanto da parte de detecção quanto das medidas a serem tomadas com os dados gerados em relação a oxigênio e pH em um ambiente de cultivo de animais aquáticos, mostrando em tempo real os dados e também as medidas aplicadas. 

### Objetivos do projeto 

O objetivo é automatizar a tanto a coleta quanto as medidas a serem tomadas se necessário para os parâmetros de oxigênio e pH, podendo ser expandido para outros parâmetros. 

 

### Descrição do funcionamento 

#### Duração e Quantidade de vezes de funcionamento 

É possível definir o tempo para gerar os dados com a variável “tempo”. 

É possível definir a quantidade de vezes que os dados serão gerados com a 	variável “ciclos”. 

#### Monitoramento dos Níveis de Oxigênio e pH 

Gera automaticamente os níveis de oxigênio e pH da água. 

Exibe os valores coletados no display OLED e no console serial. 

Categoriza os níveis em "Ideal", "Abaixo do Ideal", “Não está ideal” e "Crítico". 

#### Ajuste Manual do Oxigênio 

Se o nível de O2 for menor ou igual a 5, é possível ligar manualmente o aerador para aumentar o oxigênio apertando o botão A. 

O aerador desliga quando o nível de O2 atinge o valor 10, evitando consumo desnecessário de energia. 

O ajuste pode ser interrompido manualmente apertando o botão B. 

#### Ajuste Manual do pH 

Se o pH estiver fora do intervalo seguro (6.4 ≤ pH ≤ 8.6), é possível adicionar os produtos químicos manualmente para corrigir o mesmo 

O joystick controla a direção do ajuste: 

Para cima: reduz o pH. 

Para baixo: aumenta o pH. 

#### Monitoramento via OLED 

O display OLED exibe os valores monitorados em tempo real. 

#### Gerenciamento de Segurança 

O sistema entra em "modo de segurança" caso os níveis de O2 ou pH fiquem críticos. 

Mensagens de alerta são exibidas no console. 

Permite múltiplas ações simultâneas para que aja a correção necessária a qualquer momento 

 

### Justificativa 

O projeto foi realizado tendo em vista automatizar o ambiente da psicultura que apesar de toda a tecnologia presente nos dias atuais, esse ambiente continua ainda muito “braçal”, sendo necessário uma pessoa ir em cada açude ou tanque fazer as coletas desses parâmetros, dependendo do método é necessário fazer toda a análise em laboratório para só assim poder tomar uma decisão que a mesma normalmente é uma pessoa que tem que ir no local que precisa de um ajuste.
