#pragma once

#include <time.h>

#include <fstream>

#include <vector>

#include <map>
class cGameState;

struct sConfig {
	bool isFullscreen;
	bool isWidescreen;
	bool useVerticalSync;
	float windowMultiplier;
	bool enableMusic;
	float musicVolume;
	bool useJumpLock;
	bool useHoverLock;
};


class cApp {
public:
	cApp();
	//cApp(unsigned int width, unsigned int height, bool fullscreen);

	~cApp();

	void sleep(unsigned int mseconds);

	void loadConfig(char* fileName);

	void loadLevelConfig(const std::string fileName);
	void clearLevelConfig();
	//void loadMapsConfig(const std::string fileName)
	//void loadBackgroundConfig(const std::string fileName);

	void writeConfigBinary();
	void readConfigBinary();

	virtual void init(cApp* app);
	virtual void run(cApp* app);
	virtual void shutdown();
	virtual void render();
	virtual void update(float time);

	void setState(cGameState* gameState);

	bool getIsPaused()				const { return m_isPaused; }			void setIsPaused(bool isPaused) { m_isPaused = isPaused; };
	bool getIsLocked()				const { return m_isLocked; }			void setIsLocked(bool isLocked) { m_isLocked = isLocked; };
	bool getIsUpdatedEveryFrame()	const { return m_isUpdatedEveryFrame; }	void setIsUpdatedEveryFrame(bool isUpdatedEveryFrame) { m_isUpdatedEveryFrame = isUpdatedEveryFrame; };

	unsigned short getFpsCurrent()		const { return m_fpsCurrent; };		void setFpsCurrent(unsigned short fpsCurrent) { m_fpsCurrent = fpsCurrent; };

	unsigned short getWindowWidth()		const { return m_windowWidth; };
	unsigned short getWindowHeight()	const { return m_windowHeight; };
	unsigned short getViewWidth()		const { return m_viewWidth; };
	unsigned short getViewHeight()		const { return m_viewHeight; };
	float getWindowMultiplier()			const { return m_windowMultiplier; }	void setWindowMultiplier(float windowMultiplier) { m_windowMultiplier = windowMultiplier; };
	bool getIsFullscreen()				const { return m_isFullscreen; }		void setIsFullscreen(bool isFullscreen) { m_isFullscreen = isFullscreen; };
	bool getIsWidescreen()				const { return m_isWidescreen; }		void setIsWidescreen(bool isWidescreen) { m_isWidescreen = isWidescreen; };
	bool getUseVerticalSync()			const { return m_useVerticalSync; }		void setUseVerticalSync(bool useVerticalSync) { m_useVerticalSync = useVerticalSync; };
	bool getUseJumpLock()				const { return m_useJumpLock; }			void setUseJumpLock(bool useJumpLock) { m_useJumpLock = useJumpLock; };
	bool getUseHoverLock()				const { return m_useHoverLock; }		void setUseHoverLock(bool useHoverLock) { m_useHoverLock = useHoverLock; };
	//bool getEnableMusic()				const { return m_enableMusic; };	

	bool getDoHideForeground()	const { return m_doHideForeground; }	void setDoHideForeground(bool doHideForeground) { m_doHideForeground = doHideForeground; };
	float getWeatherColor()		const { return m_weatherColor; }		void setWeatherColor(float weatherColor) { m_weatherColor = weatherColor; };

	float getTimerState()		const { return m_timerState; }		void setTimerState(float timerState) { m_timerState = timerState; };
	float getLevelStartDelay()	const { return m_levelStartDelay; }	void setLevelStartDelay(float levelStartDelay) { m_levelStartDelay = levelStartDelay; };

	unsigned char getWeatherType()			const { return m_weatherType; }			void setWeatherType(unsigned char weatherType) { m_weatherType = weatherType; };
	unsigned short getDarkenNumerator()		const { return m_darkenNumerator; }		void setDarkenNumerator(unsigned short darkenNumerator) { m_darkenNumerator = darkenNumerator; };
	unsigned short getDarkenDenominator()	const { return m_darkenDenominator; }	void setDarkenDenominator(unsigned short darkenDenominator) { m_darkenDenominator = darkenDenominator; };
	unsigned short getLightenNumerator()	const { return m_lightenNumerator; }		void setLightenNumerator(unsigned short lightenNumerator) { m_lightenNumerator = lightenNumerator; };
	unsigned short getLightenDenominator()	const { return m_lightenDenominator; }	void setLightenDenominator(unsigned short lightenDenominator) { m_lightenDenominator = lightenDenominator; };
	bool getDoRain()						const { return m_doRain; }				void setDoRain(bool doRain) { m_doRain = doRain; };

	//std::string getPathFont()		const { return m_pathFont; }		void setPathFont(std::string pathFont) { m_pathFont = pathFont; };

	std::string getPathLevel()		const { return m_pathLevel; }		void setPathLevel(std::string pathLevel) { m_pathLevel = pathLevel; };
	std::string getPathBackground() const { return m_pathBackground; }	void setPathBackground(std::string pathBackground) { m_pathBackground = pathBackground; };
	std::string getPathForeground() const { return m_pathForeground; }	void setPathForeground(std::string pathForeground) { m_pathForeground = pathForeground; };

	void clearPathForeground();

	std::string getPathMusic(unsigned char num) const { return m_pathMusic[num]; };

	std::string getPathLeft(int num)	const { return m_pathLeft[num]; };
	std::string getPathRight(int num)	const { return m_pathRight[num]; };
	std::string getPathDoor(int num)	const { return m_pathDoor[num]; };
	std::string getPathBottom(int num)	const { return m_pathBottom[num]; };
	std::string getPathTop(int num)		const { return m_pathTop[num]; };

	std::string getPathPlayer1()		const { return m_pathPlayer1; };
	std::string getTextSign(int num)	const { return m_textSign[num]; };

	std::string getPathTextBox(unsigned char num)	const { return m_pathTextBox[num]; };

	float getMusicVolume()	const { return m_musicVolume; }		void setMusicVolume(float musicVolume) { m_musicVolume = musicVolume; };
	bool getUseEventInput()	const { return m_useEventInput; }	void setUseEventInput(bool useEventInput) { m_useEventInput = useEventInput; };

	char* getPathTrigger(unsigned char trigger);

	void clearTrains();

	

	const std::string& getTrainPath(int num) { return m_trainPaths[num]; }
	const std::vector<int>& getTrainNumber(int num) { return m_trainNumbers[num]; }
private:
	std::map<int, std::string> m_trainPaths;
	std::map<int, std::vector<int>> m_trainNumbers;

	cGameState* m_state;
	bool m_secondCall;
	bool m_isPaused;
	bool m_isRunning;
	bool m_isUpdatedEveryFrame;
	bool m_isLocked;
	bool m_isFullscreen, m_isWidescreen, m_useVerticalSync, m_useEventInput;
	bool m_useJumpLock, m_useHoverLock;
	bool m_doHideForeground;

	unsigned short m_fpsCurrent;
	int m_frameRate;
	float m_timeStep;
	float m_timerState;
	float m_levelStartDelay;

	unsigned short m_windowWidth;
	unsigned short m_windowHeight;
	unsigned short m_viewWidth;
	unsigned short m_viewHeight;
	float m_windowMultiplier;
	//bool m_enableMusic;
	float m_musicVolume;

	unsigned char m_weatherType;
	float m_weatherColor;
	unsigned short m_darkenNumerator, m_darkenDenominator, m_lightenNumerator, m_lightenDenominator;
	bool m_doRain;

	char** m_pathTrigger;

	//std::string m_pathFont;

	std::string m_pathLevel;
	std::string m_pathMusic[2];
	//std::string m_musicPath0, m_musicPath1;
	std::string m_pathBackground, m_pathForeground;

	std::string m_textSign[4];
	std::string m_pathLeft[4];
	std::string m_pathRight[4];
	std::string m_pathDoor[4];
	std::string m_pathBottom[4];
	std::string m_pathTop[4];

	std::string m_pathTextBox[4];

	std::string m_pathPlayer1;

	std::ofstream m_outputFile;




};