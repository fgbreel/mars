# -*- mode: ruby -*-
# vi: set ft=ruby :

# TODO
# - build package
# - upload somewhere
# - install onto two machines
# - have 1 test case running ok

$script = <<-SCRIPT
apt-get update && apt-get install -y gawk buffer psmisc lvm2 linux-headers-$(uname -r) dkms

init_mars_dir() {
  fallocate -l 10G foo
  losetup -f foo
  vgchange -a y
  vgcreate mars /dev/loop0
  lvcreate -n mars -L 9G mars
  mkfs -t ext4 /dev/mapper/mars-mars
  mkdir /mars
  mount /dev/mapper/mars-mars /mars/
}


init_ssh_access() {
	#sudo ssh-keygen -t ed25519 -a 100 -f /root/.ssh/marstester
	sudo mkdir --mode 0700 /root/.ssh
	sudo cat ~vagrant/.ssh/authorized_keys > /root/.ssh/authorized_keys
	sudo cat ~vagrant/.ssh/marstester > /root/.ssh/marstester
	sudo chmod 0400 /root/.ssh/marstester
	#if [ "$HOSTNAME" = "istore-test-bap7" ]; then
	#	sudo scp -i /root/.ssh/marstester vagrant@istore-test-bs7:~/.ssh/authorized_keys ~/.ssh/authorized_keys
	#if
	#sudo cat /root/.ssh/marstester.pub > /root/.ssh/authorized_keys
}

init_test_hostname() {
	sudo echo "192.168.33.10 istore-test-bs7" >> /etc/hosts
	sudo echo "192.168.33.20 istore-test-bap7" >> /etc/hosts
}

install_mars() {
	apt install -y /home/vagrant/mars*\.deb
}

init_test_hostname
init_ssh_access
init_mars_dir
install_mars

SCRIPT

MARS_INITIAL_PRIMARY_HOST="host-a"
MARS_INITIAL_SECONDARY_HOST="host-b"
MARS_SSH_KEYFILE="#{ENV['HOME']}/.vagrant.d/insecure_private_key"


Vagrant.configure("2") do |config|
  config.vm.box = "debian/stretch64"
  config.ssh.insert_key = false

  config.vm.provider "virtualbox" do |v|
    v.memory = 1024
    v.cpus = 2
  end

  config.vm.define "host-a" do |a|
    a.vm.network "private_network", ip: "192.168.33.10"
    a.vm.hostname = "istore-test-bs7"
    a.vm.provision "file", source: MARS_SSH_KEYFILE, destination: "/home/vagrant/.ssh/marstester"
    a.vm.provision "file", source: "../../mars-dkms_0.1astable118-1_amd64.deb", destination: "/home/vagrant/mars-dkms_0.1astable118-1_amd64.deb"
    a.vm.provision "file", source: "../../mars-tools_0.1astable118-1_amd64.deb", destination: "/home/vagrant/mars-tools_0.1astable118-1_amd64.deb"
    a.vm.provision "shell", inline: $script
  end

  config.vm.define "host-b" do |b|
    b.vm.network "private_network", ip: "192.168.33.20"
    b.vm.hostname = "istore-test-bap7"
    b.vm.provision "file", source: MARS_SSH_KEYFILE, destination: "/home/vagrant/.ssh/marstester"
    b.vm.provision "file", source: "../../mars-dkms_0.1astable118-1_amd64.deb", destination: "/home/vagrant/mars-dkms_0.1astable118-1_amd64.deb"
    b.vm.provision "file", source: "../../mars-tools_0.1astable118-1_amd64.deb", destination: "/home/vagrant/mars-tools_0.1astable118-1_amd64.deb"
    b.vm.provision "shell", inline: $script
  end
end
