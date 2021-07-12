#pragma once
struct BadFileFormat {
	std::string massage;
	BadFileFormat(const std::string& _massage) : massage(_massage) {}
};
struct InvalidDimensions {
	std::string massage;
	InvalidDimensions(const std::string& _massage) : massage(_massage) {}
};
struct InvalidStream {
	std::string massage;
	InvalidStream(const std::string& _massage) : massage(_massage) {}
};