# 🛠️ How to Compile GenPass

GenPass is a C/C++ project that generates passwords and stores them in a PostgreSQL database. It depends on modern libraries like `libsodium` and `libpqxx`.

---

## 📦 Dependencies

To compile GenPass **locally**, you will need the following packages:

### ✅ Install via APT (recommended for development)

```bash
sudo apt update
sudo apt install \
  util-linux \
  libsodium-dev \
  libpqxx-dev \
  uuid-dev \
  libgtest-dev \
```

### 📚 Install from source (recommended for production or stable builds)

You can also manually download and compile stable versions of the dependencies:

* **util-linux**
  → [https://git.kernel.org/pub/scm/utils/util-linux/util-linux.git/about/](https://git.kernel.org/pub/scm/utils/util-linux/util-linux.git/about/)

* **libsodium**
  → [https://doc.libsodium.org/installation#compilation-on-unix-like-systems](https://doc.libsodium.org/installation#compilation-on-unix-like-systems)

* **libpqxx (v7.10.1 recommended)**
  → [https://github.com/jtv/libpqxx/releases/tag/7.10.1](https://github.com/jtv/libpqxx/releases/tag/7.10.1)

---

## 🔧 How to Compile (Manually)

Assuming the dependencies are installed:

```bash
gcc -Iinclude main.c -o genpass -lsodium -lpqxx -lpq

./genpass
```

> If you're using CMake or a more complex structure, adjust accordingly.

---

## 🐳 Run with Docker Compose (Recommended)

You can run the entire project (including a PostgreSQL container) using Docker Compose.

### 📁 Directory structure

```
docker/
├── docker-compose.yaml
├── Dockerfile.db         # Sets up PostgreSQL with optional init SQL
└── Dockerfile.genpass    # Compiles the GenPass binary
```

### ▶️ Steps

1. Go to the Docker project directory:

   ```bash
   cd docker
   ```

2. Build and start the services:

   ```bash
   docker-compose up --build
   ```

3. The `genpass` service will start after the database is ready.

4. You can access the database using:

   ```bash
   psql -h localhost -U genpass_user -d genpass_db
   ```

---

## 🧪 Testing

If your project includes unit tests (e.g., using GoogleTest):

```bash
cmake .
make
./run_tests
```

---