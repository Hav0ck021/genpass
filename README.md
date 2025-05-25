# 🔒 GenPass - Gerenciador de Senhas Seguro

![C++](https://img.shields.io/badge/C++-17+-00599C?logo=cplusplus)
![License](https://img.shields.io/badge/License-MIT-green)
![Build](https://img.shields.io/badge/Build-Makefile-blueviolet)

**GenPass** é um gerenciador de senhas offline escrito em C++ moderno, projetado para segurança e eficiência. Armazene suas credenciais com criptografia e gere senhas robustas. (Projeto em desenvolvimento.)

## ✨ Funcionalidades

- ✅ **Geração de senhas** com critérios customizáveis
- 🔐 **Criptografia AES-256** + Argon2 (Libsodium) para senha mestra
- 💾 **Armazenamento local seguro** (PostgreSQL)
- 🔍 **Busca inteligente** por serviços/usuários
- 📊 **Auditoria de segurança** (força de senha, duplicatas)

## 🏗️  Estrutura do Projeto

```bash
GenPass/
├── config/       # Arquivos de configuração da aplicação
├── docs/         # Documentações
├── include/      # Headers (.hpp)
├── logs/         # Logs gerados
├── src/          # Implementação (.cpp)
├── tests/        # Testes unitários
└── Makefile      # Sistema de build
```

## 🤝 Contribuição
Faça um fork do projeto

Crie sua branch
```bash
git checkout -b feature/foo
```

Commit suas mudanças
```bash
git commit -am 'Add foo'
```

Push para a branch
```bash
git push origin feature/foo
```

Abra um Pull Request

## 📄 Licença
Distribuído sob licença MIT. Veja LICENSE para mais informações.

<p align="center"> Desenvolvido por <a href="https://github.com/Hav0ck021">Caio Gabriel</a></p>
