#pragma once
#include "Profile.h"
class Vote {
	Profile votedProfile;
public:
	Vote(Profile givenProfile)
	{
		votedProfile = givenProfile;
	}
	void addVote() {
		votedProfile.setVoteCount(votedProfile.getVoteCount() + 1);
	}
};