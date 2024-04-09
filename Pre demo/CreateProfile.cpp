#include "CreateProfile.h"


void CreateProfile::createProfile(string username, SendDataClient& sendDataClient, ReadDataClient& readDataClient, LogClass& logger) {
	packetClass createProfilePacket;
	createProfilePacket.Head.packetType = PacketTypes::CreateProfilePacket;
	cout << "Enter profile information:" << endl;
	cout << "First name: ";
	string firstName;
	cin >> firstName;
	cout << "Last name: ";
	string lastName;
	cin >> lastName;
	cout << "Bio: ";
	string bio;
	cin >> bio;
	cout << "User class: ";
	string userClass;
	cin >> userClass;

	//create random id
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(0, 10000);
	int id = dis(gen);

	createProfilePacket.profile = Profile(username + "," + firstName + "," + lastName + "," + bio + "," + userClass + "," + to_string(id) + ",0");
	sendDataClient.sendPacket(createProfilePacket);
	readDataClient.receivePacket(createProfilePacket);

	if (createProfilePacket.Head.packetType == PacketTypes::ProfileRequestPacket) {
		cout << "Profile created successfully." << endl;
		cout << "Your Profile id is " << id << endl;
		ostringstream profileStream;
		profileStream << createProfilePacket.profile.userName << ","
			<< createProfilePacket.profile.firstName << ","
			<< createProfilePacket.profile.lastName << ","
			<< createProfilePacket.profile.bio << ","
			<< createProfilePacket.profile.userClass << ","
			<< createProfilePacket.profile.id << ","
			<< createProfilePacket.profile.voteCount;
		logger.PrintToFile("Profile Created: " + profileStream.str());
	}
	else {
		cout << "Profile creation failed." << endl;
		ostringstream profileStream;
		profileStream << createProfilePacket.profile.userName << ","
			<< createProfilePacket.profile.firstName << ","
			<< createProfilePacket.profile.lastName << ","
			<< createProfilePacket.profile.bio << ","
			<< createProfilePacket.profile.userClass << ","
			<< createProfilePacket.profile.id << ","
			<< createProfilePacket.profile.voteCount;
		logger.PrintToFile("Profile Created: " + profileStream.str());
	}
}

