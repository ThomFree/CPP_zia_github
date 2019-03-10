# Install fedora 28 image, as the "moulinette"
FROM docker.io/fedora

RUN dnf install -y \
    gcc \
    gcc-c++ \
    make \
    cmake \
    python3

# Create the working directory
RUN mkdir -p /zia
RUN mkdir -p /zia/build
WORKDIR /zia

# Copy the project files into it
COPY . .

RUN pip3 install --no-cache-dir conan

# Run the command launched by the "moulinette" as stated in the subject
RUN cd build && conan install .. --build=missing && cmake .. -G "Unix Makefiles" && cmake --build .

# Finally, launch the Zia ;)
CMD ["./build/bin/zia"]