#pragma once

#include "Util.h"
using namespace System;
using namespace System::Collections::Generic;

#include "sc2replay/info.h"

namespace SC2ReplayNet {

	public ref struct PlayerDisplay
	{
	public:
		PlayerDisplay(const sc2replay::PlayerDisplay *disp) : display(disp)
		{

		}
  
	public:
		bool operator==(PlayerDisplay other) {
			return name==other.name && race==other.race && color==other.color;
		}
  
	public:
		property String^ name
		{
			String^ get()
			{
				return gcnew String(display->name.c_str());
			}
		}

		property String^ race
		{
			String^ get()
			{
				return gcnew String(display->name.c_str());
			}
		}

		property String^ color
		{
			String^ get()
			{
				return gcnew String(display->name.c_str());
			}
		}


	private:
		const sc2replay::PlayerDisplay *display;
	};

	public ref class Info
	{
	public:
		enum class GameSpeed
		{
			SLOWER = 0x00,
			SLOW   = 0x01,
			NORMAL = 0x02,
			FAST   = 0x03,
			FASTER = 0x04
		};
  
	public:
		Info(const sc2replay::Info *inf) : info(inf)
		{
		}

		~Info()
		{
		}
  
	public:
		//void load( const uint8_t* data, off_t size );
  
	public:
		const List<String^>^ getPlayerNames() {
			sc2replay::Info::PlayerNames std_players = info->getPlayerNames();
			List<String^>^ players = gcnew List<String^>();
			MarshalVectorToList<std::string, String^>(std_players, players);
			return players;
		}
		
		const sc2replay::uint8_t getNumberOfPlayers() {
			return info->getNumberOfPlayers();
		}

		const sc2replay::uint8_t getNumberOfSlots() {
			return info->getNumberOfSlots();
		}

		String^ getMapFilename() {
			return gcnew String(info->getMapFilename().c_str());
		}

		String^ getMapName() {
			return gcnew String(info->getMapName().c_str());
		}

		//GameSpeed             getSpeed                 () const;
		
		bool getAllianceLocked() {
			return info->getAllianceLocked();
		}

		sc2replay::uint8_t getNumberOfPlayerDisplays() {
			return info->getNumberOfPlayerDisplays();
		}

		//const PlayerDisplays& getPlayerDisplays        () const;
		
		sc2replay::off_t getBufferSize() {
			return info->getBufferSize();
		}
		
		//sc2replay::uint8_t*              getBuffer                () const;
  
	public:
		void exportDump(String^ filename) {
			std::string std_filename;
			MarshalString(filename, std_filename);
			info->exportDump(std_filename);
		}
  
	private:
		const sc2replay::Info *info;
	};
}