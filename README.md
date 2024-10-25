# Partioning and Sorting Large Files
This project aims to apply techniques learned during Algorithms and Data Structures II course to partion large files and sort them with a given key and create indexes.



Definir duas ou tres perguntas para fazer ao conjunto de dados (Serão as consultas que serão realizadas nos dados)



## Estruturas de Dados

### 1. `CategoryEntry`
A estrutura `CategoryEntry` é utilizada para representar uma categoria de produtos. Contém os campos:

### `CategoryEntry`
- **category_id:** ID da categoria (unsigned long long)
- **category_code:** Código da categoria (char array)
- **next:** Próximo registro (long)
- **deleted:** Marca como excluído (bool)

### 2. `ProductEntry`

A estrutura `ProductEntry` é utilizada para armazenar informações sobre um produto. Contém os campos:
- **product_id:** ID do produto (int)
- **brand:** Marca do produto (char array)
- **price:** Preço do produto (float)
- **next:** Próximo registro (long)
- **deleted:** Marca como excluído (bool)


### 3. `SessionEntry`

A estrutura `SessionEntry` é usada para registrar eventos relacionados a sessões de usuários. Seus campos são:
- **event_time:** Data e hora do evento (char array)
- **event_type:** Tipo do evento (char array)
- **user_session:** ID da sessão do usuário (char array)
- **user_id:** ID do usuário (unsigned int)
- **next:** Próximo registro (long)
- **deleted:** Marca como excluído (bool)


## Estruturas dos Índices

### `NumericIndexEntry`
- **key:** Chave numérica (unsigned long long)
- **address:** Endereço do registro associado (long)

### `StringIndexEntry`
- **key:** Chave de sessão (char array)
- **address:** Endereço do registro associado (long)
- **offset:** Offset para localização (unsigned long long)