#pragma once

class C_CSGameRules {
public:
    // helper methods.
    // only valid in game.
    __forceinline C_CSGameRules *get_gamerules( ) {
        if( !g_csgo.m_engine->IsInGame() )
            return nullptr;

        return Address( this ).to< C_CSGameRules * >( );
    }

private:
    template< typename t >
	__forceinline t get( Address offset ) {
        C_CSGameRules *gr{ get_gamerules( ) };
        if( !gr )
            return t{}; // note - dex; probably a bad solution...

		return *( t *)( ( uintptr_t )gr + offset );
	}

public:
    __forceinline bool m_bFreezePeriod( ) {
        return get< bool >( 0x20 );

        // note - dex; doesnt work for some reason
        // return get< bool >( g_netvars.get( HASH( "DT_CSGameRules" ), HASH( "m_bFreezePeriod" ) ) );
    }
};

/*
    signed int sub_39F250()
    {
      signed int result; // eax
      __int128 v1; // [esp+0h] [ebp-3Ch]
      __int128 v2; // [esp+10h] [ebp-2Ch]
      __int128 v3; // [esp+20h] [ebp-1Ch]
      __int64 v4; // [esp+30h] [ebp-Ch]
    
      if ( !(dword_4FABE24 & 1) )
      {
        dword_4FABE24 |= 1u;
        sub_26D340(&dword_4FABE28);
        dword_4FABE28 = (int)"should_never_see_this";
        dword_4FABE54 = 0;
        dword_4FABE2C = 0;
        dword_4FABE30 = 0;
        dword_4FABE48 = (int)sub_26D5A0;
        sub_26D340(&dword_4FABE64);
        dword_4FABE64 = (int)"m_bFreezePeriod";
        dword_4FABE90 = 32;
        dword_4FABE68 = 0;
        dword_4FABE6C = 0;
        dword_4FABE84 = (int)sub_26D5D0;
        sub_26D340(&dword_4FABEA0);
        dword_4FABEA0 = (int)"m_bMatchWaitingForResume";
        dword_4FABECC = 64;
        dword_4FABEA4 = 0;
        dword_4FABEA8 = 0;
        dword_4FABEC0 = (int)sub_26D5D0;
        sub_26D340(&dword_4FABEDC);
        dword_4FABEDC = (int)"m_bWarmupPeriod";
        dword_4FABF08 = 33;
        dword_4FABEE0 = 0;
        dword_4FABEE4 = 0;
        dword_4FABEFC = (int)sub_26D5D0;
        sub_26D340(&dword_4FABF18);
        dword_4FABF18 = (int)"m_fWarmupPeriodEnd";
        dword_4FABF44 = 36;
        dword_4FABF1C = 1;
        dword_4FABF20 = 0;
        dword_4FABF38 = (int)sub_26D5A0;
        sub_26D340(&dword_4FABF54);
        dword_4FABF54 = (int)"m_fWarmupPeriodStart";
        dword_4FABF80 = 40;
        dword_4FABF58 = 1;
        dword_4FABF5C = 0;
        dword_4FABF74 = (int)sub_26D5A0;
        sub_26D340(&dword_4FABF90);
        dword_4FABF90 = (int)"m_bTerroristTimeOutActive";
        dword_4FABFBC = 44;
        dword_4FABF94 = 0;
        dword_4FABF98 = 0;
        dword_4FABFB0 = (int)sub_26D5D0;
        sub_26D340(&dword_4FABFCC);
        dword_4FABFCC = (int)"m_bCTTimeOutActive";
        dword_4FABFF8 = 45;
        dword_4FABFD0 = 0;
        dword_4FABFD4 = 0;
        dword_4FABFEC = (int)sub_26D5D0;
        sub_26D340(&dword_4FAC008);
        dword_4FAC008 = (int)"m_flTerroristTimeOutRemaining";
        dword_4FAC034 = 48;
        dword_4FAC00C = 1;
        dword_4FAC010 = 0;
        dword_4FAC028 = (int)sub_26D5A0;
        sub_26D340(&dword_4FAC044);
        dword_4FAC044 = (int)"m_flCTTimeOutRemaining";
        dword_4FAC070 = 52;
        dword_4FAC048 = 1;
        dword_4FAC04C = 0;
        dword_4FAC064 = (int)sub_26D5A0;
        sub_26D340(&dword_4FAC080);
        dword_4FAC080 = (int)"m_nTerroristTimeOuts";
        dword_4FAC0AC = 56;
        dword_4FAC084 = 0;
        dword_4FAC088 = 0;
        dword_4FAC0A0 = (int)sub_26D5A0;
        sub_26D340(&dword_4FAC0BC);
        dword_4FAC0BC = (int)"m_nCTTimeOuts";
        dword_4FAC0E8 = 60;
        dword_4FAC0C0 = 0;
        dword_4FAC0C4 = 0;
        dword_4FAC0DC = (int)sub_26D5A0;
        sub_26D340(&dword_4FAC0F8);
        dword_4FAC0F8 = (int)"m_iRoundTime";
        dword_4FAC124 = 68;
        dword_4FAC0FC = 0;
        dword_4FAC100 = 0;
        dword_4FAC118 = (int)sub_26D5A0;
        sub_26D340(&dword_4FAC134);
        dword_4FAC134 = (int)"m_gamePhase";
        dword_4FAC160 = 96;
        dword_4FAC138 = 0;
        dword_4FAC13C = 0;
        dword_4FAC154 = (int)sub_26D5A0;
        sub_26D340(&dword_4FAC170);
        dword_4FAC170 = (int)"m_totalRoundsPlayed";
        dword_4FAC19C = 100;
        dword_4FAC174 = 0;
        dword_4FAC178 = 0;
        dword_4FAC190 = (int)sub_26D5A0;
        sub_26D340(&dword_4FAC1AC);
        dword_4FAC1AC = (int)"m_nOvertimePlaying";
        dword_4FAC1D8 = 104;
        dword_4FAC1B0 = 0;
        dword_4FAC1B4 = 0;
        dword_4FAC1CC = (int)sub_26D5A0;
        sub_26D340(&dword_4FAC1E8);
        dword_4FAC1E8 = (int)"m_timeUntilNextPhaseStarts";
        dword_4FAC214 = 92;
        dword_4FAC1EC = 1;
        dword_4FAC1F0 = 0;
        dword_4FAC208 = (int)sub_26D5A0;
        sub_26D340(&dword_4FAC224);
        dword_4FAC224 = (int)"m_flCMMItemDropRevealStartTime";
        dword_4FAC250 = 2160;
        dword_4FAC228 = 1;
        dword_4FAC22C = 0;
        dword_4FAC244 = (int)sub_26D5A0;
        sub_26D340(&dword_4FAC260);
        dword_4FAC260 = (int)"m_flCMMItemDropRevealEndTime";
        dword_4FAC28C = 2164;
        dword_4FAC264 = 1;
        dword_4FAC268 = 0;
        dword_4FAC280 = (int)sub_26D5A0;
        sub_26D340(&dword_4FAC29C);
        dword_4FAC29C = (int)"m_fRoundStartTime";
        dword_4FAC2C8 = 76;
        dword_4FAC2A0 = 1;
        dword_4FAC2A4 = 0;
        dword_4FAC2BC = (int)sub_26D5A0;
        sub_26D340(&dword_4FAC2D8);
        dword_4FAC2D8 = (int)"m_bGameRestart";
        dword_4FAC304 = 84;
        dword_4FAC2DC = 0;
        dword_4FAC2E0 = 0;
        dword_4FAC2F8 = (int)sub_26D5D0;
        sub_26D340(&dword_4FAC314);
        dword_4FAC314 = (int)"m_flRestartRoundTime";
        dword_4FAC340 = 80;
        dword_4FAC318 = 1;
        dword_4FAC31C = 0;
        dword_4FAC334 = (int)sub_26D5A0;
        sub_26D340(&dword_4FAC350);
        dword_4FAC350 = (int)"m_flGameStartTime";
        dword_4FAC37C = 88;
        dword_4FAC354 = 1;
        dword_4FAC358 = 0;
        dword_4FAC370 = (int)sub_26D5A0;
        sub_26D340(&dword_4FAC38C);
        dword_4FAC38C = (int)"m_iHostagesRemaining";
        dword_4FAC3B8 = 108;
        dword_4FAC390 = 0;
        dword_4FAC394 = 0;
        dword_4FAC3AC = (int)sub_26D5A0;
        sub_26D340(&dword_4FAC3C8);
        dword_4FAC3C8 = (int)"m_bAnyHostageReached";
        dword_4FAC3F4 = 112;
        dword_4FAC3CC = 0;
        dword_4FAC3D0 = 0;
        dword_4FAC3E8 = (int)sub_26D5D0;
        sub_26D340(&dword_4FAC404);
        dword_4FAC404 = (int)"m_bMapHasBombTarget";
        dword_4FAC430 = 113;
        dword_4FAC408 = 0;
        dword_4FAC40C = 0;
        dword_4FAC424 = (int)sub_26D5D0;
        sub_26D340(&dword_4FAC440);
        dword_4FAC440 = (int)"m_bMapHasRescueZone";
        dword_4FAC46C = 114;
        dword_4FAC444 = 0;
        dword_4FAC448 = 0;
        dword_4FAC460 = (int)sub_26D5D0;
        sub_26D340(&dword_4FAC47C);
        dword_4FAC47C = (int)"m_bMapHasBuyZone";
        dword_4FAC4A8 = 115;
        dword_4FAC480 = 0;
        dword_4FAC484 = 0;
        dword_4FAC49C = (int)sub_26D5D0;
        sub_26D340(&dword_4FAC4B8);
        dword_4FAC4B8 = (int)"m_bIsQueuedMatchmaking";
        dword_4FAC4E4 = 116;
        dword_4FAC4BC = 0;
        dword_4FAC4C0 = 0;
        dword_4FAC4D8 = (int)sub_26D5D0;
        sub_26D340(&dword_4FAC4F4);
        dword_4FAC4F4 = (int)"m_bIsValveDS";
        dword_4FAC520 = 117;
        dword_4FAC4F8 = 0;
        dword_4FAC4FC = 0;
        dword_4FAC514 = (int)sub_26D5D0;
        sub_26D340(&dword_4FAC530);
        dword_4FAC530 = (int)"m_bIsQuestEligible";
        dword_4FAC55C = 2169;
        dword_4FAC534 = 0;
        dword_4FAC538 = 0;
        dword_4FAC550 = (int)sub_26D5D0;
        sub_26D340(&dword_4FAC56C);
        dword_4FAC56C = (int)"m_bLogoMap";
        dword_4FAC598 = 118;
        dword_4FAC570 = 0;
        dword_4FAC574 = 0;
        dword_4FAC58C = (int)sub_26D5D0;
        sub_26D340(&dword_4FAC5A8);
        dword_4FAC5A8 = (int)"m_iNumGunGameProgressiveWeaponsCT";
        dword_4FAC5D4 = 120;
        dword_4FAC5AC = 0;
        dword_4FAC5B0 = 0;
        dword_4FAC5C8 = (int)sub_26D5A0;
        sub_26D340(&dword_4FAC5E4);
        dword_4FAC5E4 = (int)"m_iNumGunGameProgressiveWeaponsT";
        dword_4FAC610 = 124;
        dword_4FAC5E8 = 0;
        dword_4FAC5EC = 0;
        dword_4FAC604 = (int)sub_26D5A0;
        sub_26D340(&dword_4FAC620);
        dword_4FAC620 = (int)"m_iSpectatorSlotCount";
        dword_4FAC64C = 128;
        dword_4FAC624 = 0;
        dword_4FAC628 = 0;
        dword_4FAC640 = (int)sub_26D5A0;
        sub_26D340(&dword_4FAC65C);
        dword_4FAC65C = (int)"m_bBombDropped";
        dword_4FAC688 = 2460;
        dword_4FAC660 = 0;
        dword_4FAC664 = 0;
        dword_4FAC67C = (int)sub_26D5D0;
        sub_26D340(&dword_4FAC698);
        dword_4FAC698 = (int)"m_bBombPlanted";
        dword_4FAC6C4 = 2461;
        dword_4FAC69C = 0;
        dword_4FAC6A0 = 0;
        dword_4FAC6B8 = (int)sub_26D5D0;
        sub_26D340(&dword_4FAC6D4);
        dword_4FAC6D4 = (int)"m_iRoundWinStatus";
        dword_4FAC700 = 2464;
        dword_4FAC6D8 = 0;
        dword_4FAC6DC = 0;
        dword_4FAC6F4 = (int)sub_26D5A0;
        sub_26D340(&dword_4FAC710);
        dword_4FAC710 = (int)"m_eRoundWinReason";
        dword_4FAC73C = 2468;
        dword_4FAC714 = 0;
        dword_4FAC718 = 0;
        dword_4FAC730 = (int)sub_26D5A0;
        sub_26D340(&dword_4FAC74C);
        dword_4FAC74C = (int)"m_flDMBonusStartTime";
        dword_4FAC778 = 1100;
        dword_4FAC750 = 1;
        dword_4FAC754 = 0;
        dword_4FAC76C = (int)sub_26D5A0;
        sub_26D340(&dword_4FAC788);
        dword_4FAC788 = (int)"m_flDMBonusTimeLength";
        dword_4FAC7B4 = 1104;
        dword_4FAC78C = 1;
        dword_4FAC790 = 0;
        dword_4FAC7A8 = (int)sub_26D5A0;
        sub_26D340(&dword_4FAC7C4);
        dword_4FAC7C4 = (int)"m_unDMBonusWeaponLoadoutSlot";
        dword_4FAC7F0 = 1108;
        dword_4FAC7C8 = 0;
        dword_4FAC7CC = 0;
        dword_4FAC7E4 = (int)sub_26D5E0;
        sub_26D340(&dword_4FAC800);
        dword_4FAC800 = (int)"m_bDMBonusActive";
        dword_4FAC82C = 1110;
        dword_4FAC804 = 0;
        dword_4FAC808 = 0;
        dword_4FAC820 = (int)sub_26D5D0;
        sub_26D340(&dword_4FAC83C);
        dword_4FAC83C = (int)"m_bTCantBuy";
        dword_4FAC868 = 2472;
        dword_4FAC840 = 0;
        dword_4FAC844 = 0;
        dword_4FAC85C = (int)sub_26D5D0;
        sub_26D340(&dword_4FAC878);
        dword_4FAC878 = (int)"m_bCTCantBuy";
        dword_4FAC8A4 = 2473;
        dword_4FAC87C = 0;
        dword_4FAC880 = 0;
        dword_4FAC898 = (int)sub_26D5D0;
        sub_26D340(&dword_4FAC8B4);
        dword_4FAC8B4 = (int)"m_flGuardianBuyUntilTime";
        dword_4FAC8E0 = 2476;
        dword_4FAC8B8 = 1;
        dword_4FAC8BC = 0;
        dword_4FAC8D4 = (int)sub_26D5A0;
        sub_26D340(&v1);
        LODWORD(v1) = "m_iMatchStats_RoundResults[0]";
        *(_QWORD *)((char *)&v1 + 4) = 0i64;
        HIDWORD(v3) = 2480;
        LODWORD(v3) = sub_26D5A0;
        sub_26D420(2480, 4, 30, v1, v2, v3, v4);
        sub_26D340(&v1);
        LODWORD(v1) = "m_iMatchStats_PlayersAlive_T[0]";
        *(_QWORD *)((char *)&v1 + 4) = 0i64;
        HIDWORD(v3) = 2720;
        LODWORD(v3) = sub_26D5A0;
        sub_26D420(2720, 4, 30, v1, v2, v3, v4);
        sub_26D340(&v1);
        LODWORD(v1) = "m_iMatchStats_PlayersAlive_CT[0]";
        *(_QWORD *)((char *)&v1 + 4) = 0i64;
        HIDWORD(v3) = 2600;
        LODWORD(v3) = sub_26D5A0;
        sub_26D420(2600, 4, 30, v1, v2, v3, v4);
        sub_26D340(&v1);
        LODWORD(v1) = "m_GGProgressiveWeaponOrderCT[0]";
        *(_QWORD *)((char *)&v1 + 4) = 0i64;
        HIDWORD(v3) = 132;
        LODWORD(v3) = sub_26D5A0;
        sub_26D420(132, 4, 60, v1, v2, v3, v4);
        sub_26D340(&v1);
        LODWORD(v1) = "m_GGProgressiveWeaponOrderT[0]";
        *(_QWORD *)((char *)&v1 + 4) = 0i64;
        HIDWORD(v3) = 372;
        LODWORD(v3) = sub_26D5A0;
        sub_26D420(372, 4, 60, v1, v2, v3, v4);
        sub_26D340(&v1);
        LODWORD(v1) = "m_GGProgressiveWeaponKillUpgradeOrderCT[0]";
        *(_QWORD *)((char *)&v1 + 4) = 0i64;
        HIDWORD(v3) = 612;
        LODWORD(v3) = sub_26D5A0;
        sub_26D420(612, 4, 60, v1, v2, v3, v4);
        sub_26D340(&v1);
        LODWORD(v1) = "m_GGProgressiveWeaponKillUpgradeOrderT[0]";
        HIDWORD(v3) = 852;
        *(_QWORD *)((char *)&v1 + 4) = 0i64;
        LODWORD(v3) = sub_26D5A0;
        sub_26D420(852, 4, 60, v1, v2, v3, v4);
        sub_26D340(&dword_4FACA94);
        dword_4FACA94 = (int)"m_MatchDevice";
        dword_4FACAC0 = 1092;
        dword_4FACA98 = 0;
        dword_4FACA9C = 0;
        dword_4FACAB4 = (int)sub_26D5A0;
        sub_26D340(&dword_4FACAD0);
        dword_4FACAD0 = (int)"m_bHasMatchStarted";
        dword_4FACAFC = 1096;
        dword_4FACAD4 = 0;
        dword_4FACAD8 = 0;
        dword_4FACAF0 = (int)sub_26D5D0;
        sub_26D340(&v1);
        LODWORD(v1) = "m_TeamRespawnWaveTimes[0]";
        *(_QWORD *)((char *)&v1 + 4) = 1i64;
        HIDWORD(v3) = 2840;
        LODWORD(v3) = sub_26D5A0;
        sub_26D420(2840, 4, 32, v1, v2, v3, v4);
        sub_26D340(&v1);
        LODWORD(v1) = "m_flNextRespawnWave[0]";
        *(_QWORD *)((char *)&v1 + 4) = 1i64;
        HIDWORD(v3) = 2968;
        LODWORD(v3) = sub_26D5A0;
        sub_26D420(2968, 4, 32, v1, v2, v3, v4);
        sub_26D340(&dword_4FACB84);
        dword_4FACB84 = (int)"m_nNextMapInMapgroup";
        dword_4FACBB0 = 1112;
        dword_4FACB88 = 0;
        dword_4FACB8C = 0;
        dword_4FACBA4 = (int)sub_26D5A0;
        sub_26D340(&v1);
        LODWORD(v1) = "m_nEndMatchMapGroupVoteTypes[0]";
        *(_QWORD *)((char *)&v1 + 4) = 0i64;
        HIDWORD(v3) = 3104;
        LODWORD(v3) = sub_26D5A0;
        sub_26D420(3104, 4, 10, v1, v2, v3, v4);
        sub_26D340(&v1);
        LODWORD(v1) = "m_nEndMatchMapGroupVoteOptions[0]";
        *(_QWORD *)((char *)&v1 + 4) = 0i64;
        HIDWORD(v3) = 3144;
        LODWORD(v3) = sub_26D5A0;
        sub_26D420(3144, 4, 10, v1, v2, v3, v4);
        sub_26D340(&dword_4FACC38);
        dword_4FACC38 = (int)"m_nEndMatchMapVoteWinner";
        dword_4FACC64 = 3184;
        dword_4FACC3C = 0;
        dword_4FACC40 = 0;
        dword_4FACC58 = (int)sub_26D5A0;
        sub_26D340(&dword_4FACC74);
        dword_4FACC74 = (int)"m_bIsDroppingItems";
        dword_4FACCA0 = 2168;
        dword_4FACC78 = 0;
        dword_4FACC7C = 0;
        dword_4FACC94 = (int)sub_26D5D0;
        sub_26D340(&dword_4FACCB0);
        dword_4FACCB0 = (int)"m_iActiveAssassinationTargetMissionID";
        dword_4FACCDC = 3096;
        dword_4FACCB4 = 0;
        dword_4FACCB8 = 0;
        dword_4FACCD0 = (int)sub_26D5A0;
        sub_26D340(&dword_4FACCEC);
        dword_4FACCEC = (int)"m_fMatchStartTime";
        dword_4FACD18 = 72;
        dword_4FACCF0 = 1;
        dword_4FACCF4 = 0;
        dword_4FACD0C = (int)sub_26D5A0;
        sub_26D340(&dword_4FACD28);
        dword_4FACD28 = (int)"m_szTournamentEventName";
        dword_4FACD54 = 1116;
        dword_4FACD2C = 4;
        dword_4FACD30 = 0;
        dword_4FACD34 = 260;
        dword_4FACD48 = (int)sub_26D600;
        sub_26D340(&dword_4FACD64);
        dword_4FACD64 = (int)"m_szTournamentEventStage";
        dword_4FACD90 = 1376;
        dword_4FACD68 = 4;
        dword_4FACD6C = 0;
        dword_4FACD70 = 260;
        dword_4FACD84 = (int)sub_26D600;
        sub_26D340(&dword_4FACDA0);
        dword_4FACDA0 = (int)"m_szTournamentPredictionsTxt";
        dword_4FACDCC = 1896;
        dword_4FACDA4 = 4;
        dword_4FACDA8 = 0;
        dword_4FACDAC = 260;
        dword_4FACDC0 = (int)sub_26D600;
        sub_26D340(&dword_4FACDDC);
        dword_4FACDDC = (int)"m_nTournamentPredictionsPct";
        dword_4FACE08 = 2156;
        dword_4FACDE0 = 0;
        dword_4FACDE4 = 0;
        dword_4FACDFC = (int)sub_26D5A0;
        sub_26D340(&dword_4FACE18);
        dword_4FACE18 = (int)"m_szMatchStatTxt";
        dword_4FACE44 = 1636;
        dword_4FACE1C = 4;
        dword_4FACE20 = 0;
        dword_4FACE24 = 260;
        dword_4FACE38 = (int)sub_26D600;
        sub_26D340(&dword_4FACE54);
        dword_4FACE54 = (int)"m_nGuardianModeWaveNumber";
        dword_4FACE80 = 2172;
        dword_4FACE58 = 0;
        dword_4FACE5C = 0;
        dword_4FACE74 = (int)sub_26D5A0;
        sub_26D340(&dword_4FACE90);
        dword_4FACE90 = (int)"m_nGuardianModeSpecialKillsRemaining";
        dword_4FACEBC = 2176;
        dword_4FACE94 = 0;
        dword_4FACE98 = 0;
        dword_4FACEB0 = (int)sub_26D5A0;
        sub_26D340(&dword_4FACECC);
        dword_4FACECC = (int)"m_nGuardianModeSpecialWeaponNeeded";
        dword_4FACEF8 = 2180;
        dword_4FACED0 = 0;
        dword_4FACED4 = 0;
        dword_4FACEEC = (int)sub_26D5A0;
        sub_26D340(&dword_4FACF08);
        dword_4FACF08 = (int)"m_nHalloweenMaskListSeed";
        dword_4FACF34 = 2456;
        dword_4FACF0C = 0;
        dword_4FACF10 = 0;
        dword_4FACF28 = (int)sub_26D5A0;
        sub_26D340(&dword_4FACF44);
        dword_4FACF44 = (int)"m_numGlobalGiftsGiven";
        dword_4FACF70 = 2192;
        dword_4FACF48 = 0;
        dword_4FACF4C = 0;
        dword_4FACF64 = (int)sub_26D5A0;
        sub_26D340(&dword_4FACF80);
        dword_4FACF80 = (int)"m_numGlobalGifters";
        dword_4FACFAC = 2196;
        dword_4FACF84 = 0;
        dword_4FACF88 = 0;
        dword_4FACFA0 = (int)sub_26D5A0;
        sub_26D340(&dword_4FACFBC);
        dword_4FACFBC = (int)"m_numGlobalGiftsPeriodSeconds";
        dword_4FACFE8 = 2200;
        dword_4FACFC0 = 0;
        dword_4FACFC4 = 0;
        dword_4FACFDC = (int)sub_26D5A0;
        sub_26D340(&v1);
        LODWORD(v1) = "m_arrFeaturedGiftersAccounts[0]";
        *(_QWORD *)((char *)&v1 + 4) = 0i64;
        HIDWORD(v3) = 2204;
        LODWORD(v3) = sub_26D5A0;
        sub_26D420(2204, 4, 4, v1, v2, v3, v4);
        sub_26D340(&v1);
        LODWORD(v1) = "m_arrFeaturedGiftersGifts[0]";
        *(_QWORD *)((char *)&v1 + 4) = 0i64;
        HIDWORD(v3) = 2220;
        LODWORD(v3) = sub_26D5A0;
        sub_26D420(2220, 4, 4, v1, v2, v3, v4);
        sub_26D340(&v1);
        LODWORD(v1) = "m_arrProhibitedItemIndices[ 0 ]";
        *(_QWORD *)((char *)&v1 + 4) = 0i64;
        HIDWORD(v3) = 2236;
        LODWORD(v3) = sub_26D5E0;
        sub_26D420(2236, 2, 100, v1, v2, v3, v4);
        sub_26D340(&dword_4FAD0AC);
        dword_4FAD0AC = (int)"m_numBestOfMaps";
        dword_4FAD0D8 = 2452;
        dword_4FAD0B0 = 0;
        dword_4FAD0B4 = 0;
        dword_4FAD0CC = (int)sub_26D5A0;
        sub_26D340(&v1);
        LODWORD(v1) = "m_arrTournamentActiveCasterAccounts[0]";
        *(_QWORD *)((char *)&v1 + 4) = 0i64;
        HIDWORD(v3) = 2436;
        LODWORD(v3) = sub_3A3810;
        sub_26D420(2436, 4, 4, v1, v2, v3, v4);
      }
      dword_4ED4D6C = (int)&dword_4FABE64;
      result = 1;
      dword_4ED4D70 = 80;
      dword_4ED4D74 = 0;
      dword_4ED4D78 = (int)"DT_CSGameRules";
      word_4ED4D7C = 0;
      return result;
    }
*/

/*
    2007 leaked src

    RecvPropBool( RECVINFO( m_bFreezePeriod ) ),
    RecvPropInt( RECVINFO( m_iRoundTime ) ),
    RecvPropFloat( RECVINFO( m_fRoundStartTime ) ),
    RecvPropFloat( RECVINFO( m_flGameStartTime ) ),
    RecvPropInt( RECVINFO( m_iHostagesRemaining ) ),
    RecvPropBool( RECVINFO( m_bMapHasBombTarget ) ),
    RecvPropBool( RECVINFO( m_bMapHasRescueZone ) ),
    RecvPropBool( RECVINFO( m_bLogoMap ) ),
    RecvPropBool( RECVINFO( m_bBlackMarket ) )
*/

/*
    CCSGameRules::DumpTimers (server)

    v9 = (void *)sub_1013C070((int)&v53, "Timers and related info at %f:\n", *(float *)(v2 + 16));
    sub_103CC0B0(v4, v9);
    v10 = (void *)sub_1013C070((int)&v53, "m_bCompleteReset: %d\n", *(unsigned __int8 *)(this + 3797));
    sub_103CC0B0(v4, v10);
    v11 = (void *)sub_1013C070((int)&v53, "m_iTotalRoundsPlayed: %d\n", *(_DWORD *)(this + 3744));
    sub_103CC0B0(v4, v11);
    v12 = (void *)sub_1013C070((int)&v53, "m_iRoundTime: %d\n", *(_DWORD *)(this + 600));
    sub_103CC0B0(v4, v12);
    v13 = (void *)sub_1013C070((int)&v53, "m_iRoundWinStatus: %d\n", *(_DWORD *)(this + 2996));
    sub_103CC0B0(v4, v13);
    v14 = (void *)sub_1013C070((int)&v53, "first connected: %d\n", *(unsigned __int8 *)(this + 3796));
    sub_103CC0B0(v4, v14);
    v15 = *(float *)(this + 12);
    v16 = (void *)sub_1013C070((int)&v53, "intermission start time: %f\n", v15);
    sub_103CC0B0(v4, v16);
    sub_102A41B0();
    v17 = (void *)sub_1013C070((int)&v53, "intermission duration: %f\n", *(float *)&v15);
    sub_103CC0B0(v4, v17);
    v18 = (void *)sub_1013C070((int)&v53, "freeze period: %d\n", *(unsigned __int8 *)(this + 564));
    sub_103CC0B0(v4, v18);
    v19 = (void *)sub_1013C070((int)&v53, "round restart time: %f\n", *(float *)(this + 612));
    sub_103CC0B0(v4, v19);
    v20 = (void *)sub_1013C070((int)&v53, "game start time: %f\n", *(float *)(this + 620));
    sub_103CC0B0(v4, v20);
    v21 = (void *)sub_1013C070((int)&v53, "m_fMatchStartTime: %f\n", *(float *)(this + 604));
    sub_103CC0B0(v4, v21);
    v22 = (void *)sub_1013C070((int)&v53, "m_fRoundStartTime: %f\n", *(float *)(this + 608));
    sub_103CC0B0(v4, v22);
    v23 = (void *)sub_1013C070((int)&v53, "freeze time: %d\n", *(_DWORD *)(this + 3756));
    sub_103CC0B0(v4, v23);
    v24 = (void *)sub_1013C070((int)&v53, "next think: %f\n", *(float *)(this + 4028));
    sub_103CC0B0(v4, v24);
    if ( (void ***)dword_108E8CBC == &off_108E8CA0 )
      v25 = (unsigned int)&off_108E8CA0 ^ dword_108E8CD0;
    else
      v25 = (*(int (**)(void))(*(_DWORD *)dword_108E8CBC + 52))();
    v26 = (void *)sub_1013C070((int)&v53, "fraglimit: %d\n", v25);
    sub_103CC0B0(v4, v26);
    if ( (void ***)dword_108ECBE4 == &off_108ECBC8 )
      v27 = (unsigned int)&off_108ECBC8 ^ dword_108ECBF8;
    else
      v27 = (*(int (**)(void))(*(_DWORD *)dword_108ECBE4 + 52))();
    v28 = (void *)sub_1013C070((int)&v53, "mp_maxrounds: %d\n", v27);
    sub_103CC0B0(v4, v28);
    if ( (void ***)dword_108ECC3C == &off_108ECC20 )
      v29 = (unsigned int)&off_108ECC20 ^ dword_108ECC50;
    else
      v29 = (*(int (**)(void))(*(_DWORD *)dword_108ECC3C + 52))();
    v30 = (void *)sub_1013C070((int)&v53, "mp_winlimit: %d\n", v29);
    sub_103CC0B0(v4, v30);
    if ( (void ***)dword_108FC0EC == &off_108FC0D0 )
      v31 = (unsigned int)&off_108FC0D0 ^ dword_108FC100;
    else
      v31 = (*(int (**)(void))(*(_DWORD *)dword_108FC0EC + 52))();
    v32 = (void *)sub_1013C070((int)&v53, "bot_quota: %d\n", v31);
    sub_103CC0B0(v4, v32);
    v33 = byte_106F5A90;
    if ( dword_108FC13C & 0x1000 )
    {
      v34 = "FCVAR_NEVER_AS_STRING";
    }
    else
    {
      v34 = byte_106F5A90;
      if ( *(_DWORD *)(dword_108FC144 + 36) )
        v34 = *(const char **)(dword_108FC144 + 36);
    }
    v35 = (void *)sub_1013C070((int)&v53, "bot_quota_mode: %s\n", v34);
    sub_103CC0B0(v4, v35);
    if ( (void ***)dword_108FC19C == &off_108FC180 )
      v36 = (unsigned int)&off_108FC180 ^ dword_108FC1B0;
    else
      v36 = (*(int (**)(void))(*(_DWORD *)dword_108FC19C + 52))();
    v37 = (void *)sub_1013C070((int)&v53, "bot_join_after_player: %d\n", v36);
    sub_103CC0B0(v4, v37);
    if ( (void ***)dword_108FC54C == &off_108FC530 )
      v38 = (unsigned int)&off_108FC530 ^ dword_108FC560;
    else
      v38 = (*(int (**)(void))(*(_DWORD *)dword_108FC54C + 52))();
    v39 = (void *)sub_1013C070((int)&v53, "bot_join_delay: %d\n", v38);
    sub_103CC0B0(v4, v39);
    if ( dword_108E8FF4 & 0x1000 )
    {
      v40 = "FCVAR_NEVER_AS_STRING";
    }
    else
    {
      v40 = byte_106F5A90;
      if ( *(_DWORD *)(dword_108E8FFC + 36) )
        v40 = *(const char **)(dword_108E8FFC + 36);
    }
    v41 = (void *)sub_1013C070((int)&v53, "nextlevel: %s\n", v40);
    sub_103CC0B0(v4, v41);
    if ( dword_108E904C & 0x1000 )
    {
      v33 = "FCVAR_NEVER_AS_STRING";
    }
    else if ( *(_DWORD *)(dword_108E9054 + 36) )
    {
      v33 = *(const char **)(dword_108E9054 + 36);
    }
    v42 = (void *)sub_1013C070((int)&v53, "nextmode: %s\n", v33);
    sub_103CC0B0(v4, v42);
    LOBYTE(v43) = 0;
    LOBYTE(v44) = 1;
    v45 = sub_103B18F0(v44, v43);
    v46 = sub_10481FF0();
    v47 = (void *)sub_1013C070((int)&v53, "%d humans and %d bots in game\n", v45, v46);
    sub_103CC0B0(v4, v47);
    v48 = (void *)sub_1013C070(
                    (int)&v53,
                    "num CTs (spawnable): %d (%d)\n",
                    *(_DWORD *)(this + 3764),
                    *(_DWORD *)(this + 3772));
    sub_103CC0B0(v4, v48);
    v49 = (void *)sub_1013C070(
                    (int)&v53,
                    "num Ts (spawnable): %d (%d)\n",
                    *(_DWORD *)(this + 3760),
                    *(_DWORD *)(this + 3768));
    sub_103CC0B0(v4, v49);
    if ( byte_10A204A8 )
    {
      v50 = (void *)sub_1013C070((int)&v53, "Game is over!\n");
      sub_103CC0B0(v4, v50);
    }
    v51 = (void *)sub_1013C070((int)&v53, "\n");
*/