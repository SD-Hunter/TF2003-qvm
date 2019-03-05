/*
 *  QWProgs-TF2003
 *  Copyright (C) 2004  [sd] angel
 *
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include "g_local.h"
#include "tf_set.h"

static const set_bits_t sv_settings_bits[] = {
  { "Clan Battle", "clan", "c", svsb_clanbattle         , false },
  { "Locked Game", "locked_game", "lg", svsb_game_locked        , false },
  { "Disable Spy", "spy_off", "", svsb_spy_off            , false },
  { "Grapple", "grapple", "g", svsb_allow_hook         , false },
  { "Old grenades", "old_grens", "og", svsb_old_grens          , true },
  { "Spy invis", "spyinvis", "s", svsb_invis_only         , false },
  { "Server conc grenade", "svconc", "", svsb_svconc             , true },
  { "Drop Goals", "allow_drop_goal", "adg", svsb_allow_drop_goal    , false },
  { "Additional pipebomb", "add_pipe", "", svsb_add_pipe           , true },
  { "New flash", "new_flash", "nf", svsb_new_flash          , true  },
  { "Disable powerups", "disable_powerups", "dp", svsb_disable_powerups   , false },
  { "Birthday mode", "bd", "", svsb_birthday           , false },
  { "Old spanner", "old_spanner", "", svsb_old_spanner        , false },
  { "Flag timer", "flag_timer", "ft", svsb_flag_timer         , true  },
  { "Detpack blocking", "dtpb", "", svsb_detpack_block      , true  },
  { "Sniper range fix", "snip_range_fix", "srf", svsb_snip_range_fix     , false },
  { "Random team spawn", "random_team_spawn", "rts", svsb_random_tf_spawn    , true  },
  { "Lan Mode", "lan", "", svsb_lan_mode           , false },
  { "MTFL settings", "mtfl", "", svsb_mtfl               , false },
  { "Bots", "enable_bot", "", svsb_enable_bot         , false },
  { "Training ground", "tg", "", svsb_tg_enabled         , false },
  { "SG New Find", "sg_newfind", "", svsb_sg_newfind        , true  },
  { "SG New Rockets", "sg_rfire", "", svsb_sg_rfire        , true  },
  { "Pyro flame walls", "pyrotype", "", svsb_pyrotype        , false  },
  { NULL, },
};
static const set_bits_t toggleflags_bits[] = {
  { "Autoteam", "", "", TFLAG_AUTOTEAM         , false },
  { "Teamfrags", "teamfrags", "t", TFLAG_TEAMFRAGS         , false },
  { "Fullteamscore", "fullteamscore", "fts", TFLAG_FULLTEAMSCORE         , false },
  { "Respawn delay", "", "", TFLAG_RESPAWNDELAY         , false },
  { NULL, },
};
static const set_bits_t tf_set_gren2box[] = {
  { "Drop Health          ", "", "", BP_TYPE_HEALTH , false },
  { "Drop Armor           ", "", "", BP_TYPE_ARMOR , false },
  { "Drop Detpack         ", "", "", BP_TYPE_DETPACK , false },
  { "Drop Grenades        ", "", "", BP_GREN , false },
  { "Drop Grenades by type", "", "", BP_GREN_BYTYPE , false },
  { NULL, },
};

static const set_bits_t tf_set_disablegren[] = {
    { "Normal    ", "", "", DG_TYPE_NORMAL  , false },
    { "Concussion", "", "", DG_TYPE_CONCUSSION , false },
    { "Nail      ", "", "", DG_TYPE_NAIL, false },
    { "Mirv      ", "", "", DG_TYPE_MIRV , false },
    { "Napalm    ", "", "", DG_TYPE_NAPALM, false },
    { "Flare     ", "", "", DG_TYPE_FLARE  , false },
    { "Gas       ", "", "", DG_TYPE_GAS  , false },
    { "Emp       ", "", "", DG_TYPE_EMP   , false },
    { "Flash     ", "", "", DG_TYPE_FLASH  , false },
    { "Caltrops  ", "", "", DG_TYPE_CALTROPS, false },
    { "Detpack   ", "", "", DG_TYPE_DETPACK  , false },
    { NULL, },
};
static const set_set_t set_sg_sfire[] = {
    { "", "new", SG_SFIRE_NEW,},
	{ "", "old", SG_SFIRE_281,},
	{ "", "mtfl1", SG_SFIRE_MTFL1,},
	{ "", "mtfl2", SG_SFIRE_MTFL2,},
    { NULL, },
};

set_item_t tf_settings[] = {
    { "Settings bits", "", "",  TFS_INT_BITS, 0, sv_settings_bits, NULL, "0" },
    { "Toggle flags", "", "",  TFS_INT_BITS, 0, toggleflags_bits, NULL, "0" },
    { "Autoteam time", "autoteam", "a",  TFS_FLOAT, 0, NULL, NULL, "0"  },
    { "Respawn delay", "respawn_delay", "rd",  TFS_FLOAT, 0, NULL, NULL, "0"  },
    { "Prematch time", "prematch", "pm",  TFS_FLOAT, 0, NULL, NULL, "0"  },
    { "CeaseFire time", "ceasefire_time", "cft",  TFS_FLOAT, 0, NULL, NULL, "0"  },
    { "Autokick time", "autokick_time", "akt",  TFS_INT, 0, NULL, NULL, "0"  },
    { "Autokick kills", "autokick_kills", "akk",  TFS_INT, 0, NULL, NULL, "0"  },
    { "Cheat Pause", "cheat_pause", "cp",  TFS_INT, 0, NULL, NULL, "1"  },
    { "Disable Grenades", "disable_grens", "dg",  TFS_INT_BITS, 0, tf_set_disablegren, NULL, "0"  },
    { "Sentry ppl emulation", "sgppl", "",  TFS_INT, 12, NULL, NULL, "12"  },
    { "Sentry shells fire", "sg_sfire", "",  TFS_INT_SET, SG_SFIRE_NEW, NULL, set_sg_sfire, "0"  },
    { "Sniper fps", "snip_fps", "sf",  TFS_INT, 0, NULL, NULL, "72"  },
    { "Sniper ammo on shot", "snip_ammo", "",  TFS_INT, 0, NULL, NULL, "1"  },
    { "Sniper reload time", "snip_time", "",  TFS_FLOAT, 0, NULL, NULL, "1.5" },
    { "Gas grenade effects", "new_gas", "",  TFS_INT, 131, NULL, NULL, "131"  },
    { "Extended backpack", "gren2box", "g2b",  TFS_INT_BITS, 0, tf_set_gren2box, NULL, "0"  },
    { "Arena Mode", "arena", "",  TFS_INT, 0, NULL, NULL, "0"  },
    { NULL } 
};

char           *G_NewString( const char *string );
static void _tfset_print_bits( unsigned int  val, const set_bits_t* sb )
{
    for(; sb->name; sb++ ){
        G_conprintf( "%s:%s: %s\n", sb->key, sb->name, val & sb->bit ? _ON: _OFF );
    }
}

static qboolean _tfset_getby_key( const char* key, set_item_t** outsi, int*idx){
    set_item_t* si = &tf_settings[0];

    for(; si->name; si++ ){
        if( streq( si->key, key ) || streq( si->key2, key ) ){
            *outsi = si;
            *idx = -1;
            return true;
        }
        if( si->type == TFS_INT_BITS ){
            const set_bits_t* sb = si->bitsdesc;
            int i = 0;
            for(; sb->name; sb++, i++ ){
                if( streq( sb->key, key ) || streq( sb->key2, key ) ){
                    *outsi = si;
                    *idx = i;
                    return true;
                }
            }
        }
    }
    return false;
}

static int _tf_get_setval_by_name( const char* name, const set_set_t* ss, int default_val )
{
    for(; ss->key; ss++ ){
        if( streq( ss->key, name ) ){
            return ss->val;
        }
    }
    return default_val;
}
static const char*_tf_get_setname_by_val( int val, const set_set_t* ss )
{
    for(; ss->key; ss++ ){
        if( val == ss->val ){
            return ss->key;
        }
    }
    return "unknown";
}

static void   tf_set_val( set_item_t* si, int idx,  const char*val, qboolean oninit  )
{
    switch( si->type ){
        case TFS_INT_BITS:
            if( idx < 0 ){
                if( val && val[0] ){
                    si->val._int = atoi(val);
                }
                if( !oninit ){
                    G_conprintf( "%s:%s: %d\n", si->key, si->name, si->val._uint );
                    _tfset_print_bits( si->val._uint, si->bitsdesc );
                }
            }else{
                const set_bits_t* sb = si->bitsdesc + idx;
                qboolean bit_set = si->val._uint & sb->bit;
                if( val && val[0] ){
                    bit_set = sb->default_val;
                    if( streq( val, "on" ) || streq( val, "1" ) ){
                        bit_set = true;
                    }else if( streq( val, "off" ) || streq( val, "0" ) ){
                        bit_set = false;
                    }
                    if( bit_set ){
                        si->val._uint |= sb->bit;
                    }else{
                        si->val._uint -= si->val._uint & sb->bit;
                    }
                }
                if( !oninit )
                    G_conprintf( "%s:%s: %s\n", sb->key, sb->name, bit_set? _ON: _OFF );
            }
            break;
        case TFS_INT:
            if( val && val[0] ) si->val._int = atoi( val );
            if( !oninit ) G_conprintf( "%s:%s: %d\n", si->key, si->name, si->val._int );
            break;
        case TFS_FLOAT:
            if( val && val[0] ) si->val._int = atof( val );
            if( !oninit ) G_conprintf( "%s:%s: %.2f\n", si->key, si->name, si->val._float );
            break;
        case TFS_STRING:
            if( val && val[0] ){
                if( oninit ) {
                    si->val._str = G_NewString( val );
                }else{
                    G_conprintf( "Changing string settings allowed only by localinfo\n"
                            "%s:%s: %.2f\n", si->key, si->name, si->val._float );
                }
            }
            break;
        case TFS_BOOL:
            if( val && val[0] ){
                si->val._int = atoi(si->default_val);
                if( streq( val, "on" ) || streq( val, "1" ) ){
                    si->val._int = 1;
                }else if( streq( val, "off" ) || streq( val, "0" ) ){
                    si->val._int = 0;
                }
            }
            if( !oninit ) G_conprintf( "%s:%s: %s\n", si->key, si->name, si->val._int? _ON : _OFF );
            break;
        case TFS_INT_SET:
            if( val && val[0] ){
                si->val._int = _tf_get_setval_by_name( val, si->setdesc, atoi( si->default_val ));
            }
            if( !oninit ) G_conprintf( "%s:%s: %s\n", si->key, si->name, _tf_get_setname_by_val(si->val._int, si->setdesc ) );
            break;
        default: 
            break;
    }
}
static void   tf_set( const char* name, const char*val, qboolean oninit  )
{
    set_item_t* si;
    int idx;
    if( !_tfset_getby_key( name, &si, &idx ))
        return;
    tf_set_val( si, idx, val, oninit );
}

void TeamFortress_ShowTF(  )
{
    set_item_t* si = &tf_settings[0];
    for(; si->name; si++ ){
        switch( si->type ){
            case TFS_INT_BITS:
                {
                    const set_bits_t* sb = si->bitsdesc;
                    G_sprint( self, PRINT_HIGH,  "%s:\n", si->name);
                    for(; sb->name; sb++ ){
                        G_sprint( self, PRINT_HIGH,  "%s: %s\n", sb->name, si->val._uint & sb->bit ? _ON: _OFF );
                    }
                }
                break;
            case TFS_INT:
                G_sprint( self, PRINT_HIGH,  "%s: %d\n", si->name, si->val._int );
                break;
            case TFS_FLOAT:
                G_sprint( self, PRINT_HIGH,  "%s: %.2f\n", si->name, si->val._float );
                break;
            case TFS_STRING:
                G_sprint( self, PRINT_HIGH,  "%s: %s\n", si->name, si->val._str );
                break;
            case TFS_BOOL:
                G_sprint( self, PRINT_HIGH,  "%s: %s\n", si->name, si->val._int? _ON : _OFF );
                break;
            case TFS_INT_SET:
                G_sprint( self, PRINT_HIGH,  "%s: %s\n", si->name, _tf_get_setname_by_val(si->val._int, si->setdesc ) );
                break;
            default: 
                break;
        }
    }
    G_sprint( self, 2, _TF2003 " (build %d) " _BY_SD_ANGEL "\n" ,build_number());
    G_sprint( self, 2,  "%s\n", ANGEL_VERSION);
}
void   TF_Set_Cmd( int argc  )
{
    char    name[64];
    char    val[64] = "";

    
    if( argc == 2 ) {
        set_item_t* si = &tf_settings[0];
        for(; si->name; si++ ){
            tf_set_val( si, -1, NULL, 0 );
        }
        return;
    }

    trap_CmdArgv( 2, name, sizeof( name ) );
    if( argc == 4 ){
        trap_CmdArgv( 3, val, sizeof( val ) );
    }
    tf_set( name, val, 0 );

}

extern int     team_top_colors[5];
extern char    nextmap[64];
void   TF_LocalinfoSettings( )
{
    char    value[100];
    gedict_t *ent;
    gedict_t *te;
    int i;
    float fvar;
    set_item_t* si = &tf_settings[0];

    for(; si->name; si++ ){
        if( si->key && si->key[0] ){
            GetSVInfokeyString( si->key, si->key2, value, sizeof( value ), si->default_val);
            if( value[0] ) tf_set( si->key, value, 1);
        }
        if( si->type == TFS_INT_BITS ){
            const set_bits_t* sb = si->bitsdesc;
            for(; sb->name; sb++ ){
                if( sb->key && sb->key[0] ){
                    GetSVInfokeyString( sb->key, sb->key2, value, sizeof( value ), sb->default_val? "1":"0");
                    if( value[0] ) tf_set( sb->key, value, 1);
                }
            }
        }
    }

    /*    if( !first_decode )
          {
          G_bprint(2,"!!!BUG BUG BUG!!!\nfirst_decode != 0 %d %s\n!!!BUG BUG BUG!!!\n", tfset_toggleflags, self->s.v.netname);
          tfset_toggleflags |= TFLAG_FIRSTENTRY;
          G_bprint(2,"toggleflags %d\n", tfset_toggleflags );
          return;
          }
          first_decode = 0;*/
    memset( &tf_data, 0, sizeof(tf_data));
    tfset_toggleflags = 0; //g_globalvars.parm10;
    tf_data.flagem_checked = 0;
    //tf_data.allow_hook = 0;
    //tf_data.invis_only = 0;
    if ( coop || !deathmatch )
        tfset_toggleflags |= TFLAG_CLASS_PERSIST;
    strncpy( nextmap, mapname, sizeof(nextmap) );

    ent = trap_find( world, FOFS( s.v.classname ), "info_tfdetect" );
    if ( ent )
    {
        if ( !teamplay )
            trap_cvar_set( "teamplay", "21?TeamFortress" );

        ParseTFDetect( ent );

        if ( number_of_teams <= 0 || number_of_teams >= 5 )
            number_of_teams = 4;
    } else
    {
        ent = trap_find( world, FOFS( s.v.classname ), "info_player_team1" );
        if ( ent || CTF_Map == 1 )
        {
            CTF_Map = 1;
            if ( !teamplay )
                trap_cvar_set( "teamplay", "21?TeamFortress" );
            ent = spawn();
            ent->s.v.nextthink = g_globalvars.time + 30;
            ent->s.v.think = ( func_t ) CTF_FlagCheck;
            number_of_teams = 2;
        } else
            number_of_teams = 4;

        for(i=0; i< 5; i++)
        {
            teamlives[i] = -1;
            illegalclasses[i] = 0;
            teammaxplayers[i] = 100;
        }
        civilianteams = 0;
    }
    G_bprint( 2, "Mapname: %s\n", mapname );
    SetupTeamEqualiser();
    for(i=0; i< 5; i++)
    {
        teamfrags[i] = 0;
        teamscores[i] = 0;
    }
    UpdateServerinfoScores();
    tfset_autokick_kills = 0;
    tfset_autokick_time = 0;
    tf_data.cease_fire = 0;

    tfset_toggleflags -= ( tfset_toggleflags & TFLAG_TEAMFRAGS );

    tfset_toggleflags -= ( tfset_toggleflags & TFLAG_CHEATCHECK );

    tfset_toggleflags |= GetSVInfokeyInt( "temp1", NULL, 0 );
    tfset_toggleflags |= TFLAG_FIRSTENTRY;

    //tf_data.birthday = GetSVInfokeyBool( "bd", "birthday", false );
    if( tfset(birthday) )
    {
        te = spawn();
        te->s.v.weapon = 10;
        te->s.v.nextthink = g_globalvars.time + 60;
        te->s.v.think = ( func_t ) BirthdayTimer;
    }
    //tf_data.clanbattle = GetSVInfokeyBool( "c", "clan", false );
    if (tfset(clanbattle))
    {
        tf_data.clan_scores_dumped = 0;
        //tf_data.game_locked = 0;
        //tf_data.game_locked = GetSVInfokeyBool( "lg", "locked_game", false );
    }else{
        tfset_flagoff( game_locked );
    }

    fvar = tfset_prematch_time; //GetSVInfokeyFloat( "pm", "prematch", 0 );
    if( fvar < 0 ) fvar = 0;

    tf_data.cb_prematch_time = g_globalvars.time + fvar * 60;
    if( fvar )
    {
        tf_data.cb_prematch_time += 5;
        ent = spawn();
        ent->s.v.think = ( func_t ) PreMatch_Think;
        ent->s.v.nextthink = g_globalvars.time + 5;

        tf_data.cb_ceasefire_time = tfset_ceasefire_time;//GetSVInfokeyFloat( "cft", "ceasefire_time", 0 );

        if ( tf_data.cb_ceasefire_time > 0 )
        {
            tf_data.cb_ceasefire_time = g_globalvars.time + tf_data.cb_ceasefire_time * 60;

            if( tf_data.cb_prematch_time <= tf_data.cb_ceasefire_time + 7  )
            {
                tf_data.cb_ceasefire_time = tf_data.cb_prematch_time;
                tf_data.cb_prematch_time += 7;
            }

            tf_data.cease_fire = 1;
            /*
               G_bprint( 2, "CEASE FIRE\n" );
               te = trap_find( world, FOFS( s.v.classname ), "player" );
               while ( te )
               {
               CenterPrint( te, "CEASE FIRE\n" );
               te->tfstate = te->tfstate | TFSTATE_CANT_MOVE;
               TeamFortress_SetSpeed( te );
               te = trap_find( te, FOFS( s.v.classname ), "player" );
               }*/
            te = spawn();
            te->s.v.classname = "ceasefire";
            te->s.v.think = ( func_t ) CeaseFire_think;
            te->s.v.nextthink = g_globalvars.time + 5;
            te->s.v.weapon = 1;
        }else
            tf_data.cb_ceasefire_time = 0;
    }
    if ( timelimit && ( ( timelimit ) < tf_data.cb_prematch_time ) )
    {
        timelimit += tf_data.cb_prematch_time;

        trap_cvar_set_float( "timelimit", timelimit );
    }

    if( tfset_autoteam_time > 0 )
    {
        tfset_toggleflags |= TFLAG_AUTOTEAM;
    }else{
        tfset_toggleflags -= ( tf_data.toggleflags & TFLAG_AUTOTEAM );
    }

    /*GetSVInfokeyString( "a", "autoteam", st, sizeof( st ), "" );
      if ( !strcmp( st, "on" ) )
      tf_data.toggleflags |= TFLAG_AUTOTEAM;
      else
      {
      if ( !strcmp( st, "off" ) )
      else
      {
      if ( atoi( st ) )
      {
      tf_data.toggleflags |= TFLAG_AUTOTEAM;
      autoteam_time = atoi( st );
      }
      }
      }*/
    if( !tfset_autokick_time ){
        tfset_autokick_kills = 0;
    }

    /*if ( GetSVInfokeyBool( "t", "teamfrags", false ) )
      tf_data.toggleflags |= TFLAG_TEAMFRAGS;
      else {
      tf_data.toggleflags -= ( tf_data.toggleflags & TFLAG_TEAMFRAGS );
      }
      if ( GetSVInfokeyBool( "fts", "fullteamscore", false ) )
      tf_data.toggleflags |= TFLAG_FULLTEAMSCORE;*/

    if ( tfset_cheat_pause <= 0 ) tfset_cheat_pause = 1;

    ////top colors
    tf_data.topcolor_check = 0;

    team_top_colors[1] = GetSVInfokeyInt( "tc1", NULL, -1 );
    if ( team_top_colors[1] >= 0 && team_top_colors[1] <= 15 )
        tf_data.topcolor_check = 1;
    else
        team_top_colors[1] = TeamFortress_TeamGetColor( 1 ) - 1;

    team_top_colors[2] = GetSVInfokeyInt( "tc2", NULL, -1 );
    if ( team_top_colors[2] >= 0 && team_top_colors[2] <= 15 )
        tf_data.topcolor_check = 1;
    else
        team_top_colors[2] = TeamFortress_TeamGetColor( 2 ) - 1;


    team_top_colors[3] = GetSVInfokeyInt( "tc3", NULL, -1 );
    if ( team_top_colors[3] >= 0 && team_top_colors[3] <= 15 )
        tf_data.topcolor_check = 1;
    else
        team_top_colors[3] = TeamFortress_TeamGetColor( 3 ) - 1;

    team_top_colors[4] = GetSVInfokeyInt( "tc4", NULL, -1 );
    if ( team_top_colors[4] >= 0 && team_top_colors[4] <= 15 )
        tf_data.topcolor_check = 1;
    else
        team_top_colors[4] = TeamFortress_TeamGetColor( 4 ) - 1;



    /*        tf_data.sg_newfind = true;
              tf_data.sg_sfire   = SG_SFIRE_NEW;
              GetSVInfokeyString( "sg", NULL, st, sizeof( st ), "new" );
              if ( !strcmp( st, "old" ) )
              {
              tf_data.sg_newfind = false;
              tf_data.sg_sfire   = SG_SFIRE_281;
              }

              if ( !strcmp( st, "fix" ) )
              {
              tf_data.sg_newfind = false;
              tf_data.sg_sfire   = SG_SFIRE_MTFL2;
              }

              if ( !strcmp( st, "oldmtfl" ) )
              {
              tf_data.sg_newfind = false;
              tf_data.sg_sfire   = SG_SFIRE_MTFL1;
              }
              if ( !strcmp( st, "mtflf" ) )
              {
              tf_data.sg_newfind = true;
              tf_data.sg_sfire   = SG_SFIRE_MTFL1;
              }

              if ( !strcmp( st, "oldf" ) )
              {
              tf_data.sg_newfind = true;
              tf_data.sg_sfire   = SG_SFIRE_281;
              }

              tf_data.sg_newfind = GetSVInfokeyBool( "sg_newfind", NULL, true );

              GetSVInfokeyString( "sg_sfire", NULL, st, sizeof( st ), "new" );

              if( !strcmp(st, "old"))
              tf_data.sg_sfire = SG_SFIRE_281;

              if( !strcmp(st, "mtfl1"))
              tf_data.sg_sfire = SG_SFIRE_MTFL1;

              if( !strcmp(st, "mtfl2"))
              tf_data.sg_sfire = SG_SFIRE_MTFL2;


              GetSVInfokeyString( "sg_rfire", NULL, st, sizeof( st ), "new" );

              if( !strcmp(st, "new"))
              tf_data.sg_rfire = true;
              else
              tf_data.sg_rfire = false;

              tf_data.sgppl = GetSVInfokeyInt( "sgppl", NULL, 12 );
              if ( tf_data.sgppl < 0 )
              tf_data.sgppl = 0;*/


    memset( &tg_data, 0, sizeof(tg_data));

    /*        tf_data.arena_mode = ARENA_MODE_NONE;
              if ( !strcmp( st, "ffa" ) )
              tf_data.arena_mode = ARENA_MODE_FFA;
    //		if ( !strcmp( st, "duel" ) )
    //			tf_data.arena_mode = ARENA_MODE_DUEL;*/
    tf_data.botResupplyBetweenKills = (tfset_arena_mode)?0:1;
    //////////////
    //tf_data.respawn_delay_time = GetSVInfokeyFloat( "rd", "respawn_delay", 0 );

    if ( tfset_respawn_delay_time )
        tfset_toggleflags |= TFLAG_RESPAWNDELAY;

    if ( ( tfset_toggleflags & TFLAG_RESPAWNDELAY ) && !tfset_respawn_delay_time )
        tfset_respawn_delay_time = 5;


    /*if ( tfset_toggleflags & TFLAG_AUTOTEAM )
    {
        //tfset_toggleflags -= ( tfset_toggleflags & TFLAG_AUTOTEAM );
        ent = spawn();
        ent->s.v.nextthink = g_globalvars.time + tfset_autoteam_time;
        ent->s.v.think = ( func_t ) autoteam_think;
    }*/

    //tf_data.mtfl = GetSVInfokeyBool( "mtfl", NULL, false );
    if( tfset(mtfl) )
    {
        //    tf_data.mtfl = 1;
        tfset_flagoff( allow_hook );
        tfset_flagon( old_grens );
        tfset_flagoff( invis_only );
        tfset_cheat_pause = 1;
        tf_data.topcolor_check = 1;
        //                      team_top_colors[1] = 13;
        //                      team_top_colors[2] = 4;
        tfset_flagoff( allow_drop_goal );
        tfset_flagon( add_pipe );
        tfset_flagon( new_flash );
        tfset_new_gas = GAS_DEFAULT;

        tfset_flagon(sg_newfind);
        tfset_sg_sfire = SG_SFIRE_NEW; //FIX ME
        tfset_flagoff( sg_rfire ); //FIX ME
        tfset_sgppl = 12;
        tfset_disable_grens = 0;

        tfset_flagon( detpack_block );
        tfset_flagoff( disable_powerups );
        tfset_flagon( flag_timer );
        tfset_snip_fps = 72;
        tfset_flagoff( snip_range_fix );
        tfset_snip_ammo = 1;
        tfset_snip_time = 1.5;
        tfset_gren2box = 0;
        tfset_flagon( random_tf_spawn );
        tfset_flagoff( lan_mode );
        tfset_flagoff( pyrotype );
        tfset_flagoff( tg_enabled );
        tfset_flagoff( enable_bot );
        tfset_arena_mode = ARENA_MODE_NONE;
    } 

    //SETUP LAN CONSTANTS
    if( !tfset(lan_mode) ) 
    {
        FLAME_MAXWORLDNUM	=20;	 	// maximum number of flames in the world. DO NOT PUT BELOW 20.
        MAX_WORLD_PIPEBOMBS	=15;	 	// This is divided between teams - this is the most you should have on a net server
        MAX_WORLD_AMMOBOXES	=20;		// This is divided between teams - this is the most you should have on a net server
        GR_TYPE_MIRV_NO		=4;	 	// Number of Mirvs a Mirv Grenade breaks into
        GR_TYPE_NAPALM_NO	=8; 	 	// Number of flames napalm grenade breaks into (unused if net server)
    }else
    {
        FLAME_MAXWORLDNUM	=60;	 	// maximum number of flames in the world. DO NOT PUT BELOW 20.
        MAX_WORLD_PIPEBOMBS	=30;	 	// This is divided between teams - this is the most you should have on a net server
        MAX_WORLD_AMMOBOXES	=20;		// This is divided between teams - this is the most you should have on a net server
        GR_TYPE_MIRV_NO		=12;	 	// Number of Mirvs a Mirv Grenade breaks into
        GR_TYPE_NAPALM_NO	=12; 	 	// Number of flames napalm grenade breaks into (unused if net server)
    }

    tg_data.godmode = 0;
    tg_data.unlimit_ammo = 0;
    tg_data.unlimit_grens = 0;
    tg_data.disable_reload = 0;
    tg_data.detpack_clip = TG_DETPACK_CLIP_OWNER;
    tg_data.detpack_drop = 0;   // 1 can drop, 0 - cannot
    tg_data.disable_disarm = 0; // 0 normal, 1 - disable
    tg_data.gren_effect = 0;    //0 -default, 1 - off for all, 2 off for self
    tg_data.gren_time = 0;      //0 -full time , 10 ,5 in sek

    tg_data.sg_allow_find = TG_SG_FIND_IGNORE_TEAM;
    tg_data.sg_disable_fire = 0;
    tg_data.sg_fire_bullets = true;
    tg_data.sg_fire_rockets = true;
    tg_data.sg_fire_lighting = false;
    tg_data.sg_unlimit_ammo = false;
    tg_data.tg_sbar = 0;

    if( tfset( tg_enabled ) )
        TG_LoadSettings();

    localcmd( "exec maps/%s.cfg\n", mapname );
    if( tfset(enable_bot) )
        localcmd( "exec maps/%s.wps\n", mapname );
}
