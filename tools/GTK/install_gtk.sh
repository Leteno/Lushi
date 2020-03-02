
script_path=$(dirname $0)

pushd "$script_path"

# install gtk
echo install gtk
sudo apt-get update && sudo apt-get install -y build-essential gnome-core pkg-config devhelp libglib2.0-doc libgtk2.0-doc glade libglade2-dev libgtk2.0-dev --fix-missing

# test gtk lib
echo test gtk lib
gcc -o Helloworld Helloworld.c `pkg-config --cflags --libs gtk+-2.0` && \
    echo "pass" || echo "fail"

popd
