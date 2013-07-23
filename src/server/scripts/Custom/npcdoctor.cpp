#include "ScriptPCH.h"


class custom_npc_doctor : public CreatureScript
{
private:
    bool spell_42995,
         spell_48469,
         spell_53307,
         spell_25899,
         spell_48934,
         spell_25898,
         spell_48938,
         spell_48073,
         spell_48169,
         spell_48161;

    void SendMainMenu(Player *player, Creature *_creature)
    {
        spell_42995 = false;
        spell_48469 = false;
        spell_53307 = false;
        spell_25899 = false;
        spell_48934 = false;
        spell_25898 = false;
        spell_48938 = false;
        spell_48073 = false;
        spell_48169 = false;
        spell_48161 = false;

        if(player->GetHealth() < player->GetMaxHealth())
        {
            player->ADD_GOSSIP_ITEM(5, "Restore Health", GOSSIP_SENDER_MAIN, 101);
        }

        if(player->getPowerType() == POWER_MANA)
        {
            if(player->GetPower(POWER_MANA) < player->GetMaxPower(POWER_MANA))
            {
                player->ADD_GOSSIP_ITEM(5, "Restore Mana", GOSSIP_SENDER_MAIN, 102);
            }
        }

        player->ADD_GOSSIP_ITEM(5, "Remove Cooldown", GOSSIP_SENDER_MAIN, 103);
player->ADD_GOSSIP_ITEM(5, "Repair All items", GOSSIP_SENDER_MAIN, 106);

        switch(player->GetTeam())
        {
        case ALLIANCE:
            player->ADD_GOSSIP_ITEM(5, "Remove Exhaustion", GOSSIP_SENDER_MAIN, 104);
            break;
        case HORDE:
            player->ADD_GOSSIP_ITEM(5, "Remove Sated", GOSSIP_SENDER_MAIN, 105);
            break;
        default:
            break;
        }

        player->ADD_GOSSIP_ITEM(7, "Buffs", GOSSIP_SENDER_MAIN, 200);
        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, _creature->GetGUID());
    }

    void SendSubMenu(Player *player, Creature *_creature)
    {
        if(!player->HasAura(42995) && !spell_42995)
            player->ADD_GOSSIP_ITEM( 5, "Arcane Intellect", GOSSIP_SENDER_MAIN, 201);

        if(!player->HasAura(48469) && !spell_48469)
            player->ADD_GOSSIP_ITEM( 5, "Mark of the Wild", GOSSIP_SENDER_MAIN, 202);

        if(!player->HasAura(53307) && !spell_53307)
            player->ADD_GOSSIP_ITEM( 5, "Thorns", GOSSIP_SENDER_MAIN, 203);

        if(!player->HasAura(25899) && !spell_25899)
            player->ADD_GOSSIP_ITEM( 5, "Greater Blessing of Sanctuary", GOSSIP_SENDER_MAIN, 204);

        if(!player->HasAura(48934) && !spell_48934)
            player->ADD_GOSSIP_ITEM( 5, "Greater Blessing of Might", GOSSIP_SENDER_MAIN, 205);

        if(!player->HasAura(25898) && !spell_25898)
            player->ADD_GOSSIP_ITEM( 5, "Greater Blessing of Kings", GOSSIP_SENDER_MAIN, 206);

        if(!player->HasAura(48938) && !spell_48938)
            player->ADD_GOSSIP_ITEM( 5, "Greater Blessing of Wisdom", GOSSIP_SENDER_MAIN, 207);

        if(!player->HasAura(48073) && !spell_48073)
            player->ADD_GOSSIP_ITEM( 5, "Divine Spirit", GOSSIP_SENDER_MAIN, 208);

        if(!player->HasAura(48169) && !spell_48169)
            player->ADD_GOSSIP_ITEM( 5, "Shadow Protection", GOSSIP_SENDER_MAIN, 209);

        if(!player->HasAura(48161) && !spell_48161)
            player->ADD_GOSSIP_ITEM( 5, "Power Word: Fortitude", GOSSIP_SENDER_MAIN, 210);

        player->ADD_GOSSIP_ITEM(11, "<- Back to Main Page", GOSSIP_SENDER_MAIN, 666);
        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, _creature->GetGUID());
    }

public:
    custom_npc_doctor() : CreatureScript("custom_npc_doctor") { }

    bool OnGossipHello(Player *player, Creature *_creature)
    {
        if(player->IsInCombat())
        {
            player->CLOSE_GOSSIP_MENU();
            _creature->MonsterWhisper("You are in combat. Come back later!", player->GetGUID());
            return true;
        }

        SendMainMenu(player, _creature);
        return true;
    }

    bool OnGossipSelect(Player *player, Creature *_creature, uint32 sender, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();

        if(player->IsInCombat())
        {
            player->CLOSE_GOSSIP_MENU();
            _creature->MonsterWhisper("You are in combat. Come back later!", player->GetGUID());
            return true;
        }

        if(sender != GOSSIP_SENDER_MAIN)
            return true;

        switch(action)
        {
        /****************************************************************************************
* MAINS *
****************************************************************************************/
        case 101: //Restore Health
            player->SetHealth(player->GetMaxHealth());
            player->CastSpell(player, 61456, false);
            _creature->MonsterWhisper("Your Health has been restored.", player->GetGUID());
            break;
        case 102: //Restore Mana
            player->SetPower(POWER_MANA, player->GetMaxPower(POWER_MANA));
            player->CastSpell(player, 61456, false);
            _creature->MonsterWhisper("Your Mana has been restored.", player->GetGUID());
            break;
        case 103: //Remove Cooldown
            player->RemoveAllSpellCooldown();
            player->CastSpell(player, 75459, false);
            _creature->MonsterWhisper("Your cooldowns have been removed.", player->GetGUID());
            break;
        case 104: //Remove Exhaustion
            player->RemoveAurasDueToSpell(57723);
            player->CastSpell(player, 61456, false);
            _creature->MonsterWhisper("Exhaustion has been removed.", player->GetGUID());
            break;
        case 105: //Remove Sated
            player->RemoveAurasDueToSpell(57724);
            player->CastSpell(player, 61456, false);
            _creature->MonsterWhisper("Sated has been removed.", player->GetGUID());
            break;
case 106: //Reapir
player->DurabilityRepairAll(false, 0, false);
_creature->MonsterWhisper("your items has been repaired", player->GetGUID());
break;

        /****************************************************************************************
* BUFFS *
****************************************************************************************/
        case 200:
            //SendSubMenu(player, _creature);
            break;
        case 201: // Arcane Intellect
            _creature->CastSpell(player, 42995, false);
            spell_42995 = true;
            break;
        case 202: // Mark of the Wild
            _creature->CastSpell(player, 48469, false);
            spell_48469 = true;
            break;
        case 203: // Thorns
            _creature->CastSpell(player, 53307, false);
            spell_53307 = true;
            break;
        case 204: // Greater Blessing of Sanctuary
            _creature->CastSpell(player, 25899, false);
            spell_25899 = true;
            // REMOVE COLISION AURAS ---->>
            player->RemoveAurasDueToSpell(48934);
            player->RemoveAurasDueToSpell(25898);
            player->RemoveAurasDueToSpell(48938);
            spell_48934 = false;
            spell_25898 = false;
            spell_48938 = false;
            // <<---- REMOVE COLISION AURAS
            break;
        case 205: // Greater Blessing of Might
            _creature->CastSpell(player, 48934, false);
            spell_48934 = true;
            // REMOVE COLISION AURAS ---->>
            player->RemoveAurasDueToSpell(25899);
            player->RemoveAurasDueToSpell(25898);
            player->RemoveAurasDueToSpell(48938);
            spell_25899 = false;
            spell_25898 = false;
            spell_48938 = false;
            // <<---- REMOVE COLISION AURAS
            break;
        case 206: // Greater Blessing of Kings
            _creature->CastSpell(player, 25898, false);
            spell_25898 = true;
            // REMOVE COLISION AURAS ---->>
            player->RemoveAurasDueToSpell(25899);
            player->RemoveAurasDueToSpell(48934);
            player->RemoveAurasDueToSpell(48938);
            spell_25899 = false;
            spell_48934 = false;
            spell_48938 = false;
            // <<---- REMOVE COLISION AURAS
            break;
        case 207: // Greater Blessing of Wisdom
            _creature->CastSpell(player, 48938, false);
            spell_48938 = true;
            // REMOVE COLISION AURAS ---->>
            player->RemoveAurasDueToSpell(25899);
            player->RemoveAurasDueToSpell(48934);
            player->RemoveAurasDueToSpell(25898);
            spell_25899 = false;
            spell_48934 = false;
            spell_25898 = false;
            // <<---- REMOVE COLISION AURAS
            break;
        case 208: // Divine Spirit
            _creature->CastSpell(player, 48073, false);
            spell_48073 = true;
            break;
        case 209: // Shadow Protection
            _creature->CastSpell(player, 48169, false);
            spell_48169 = true;
            break;
        case 210: // Power Word: Fortitude
            _creature->CastSpell(player, 48161, false);
            spell_48161 = true;
            break;

        /****************************************************************************************
* MAIN MENU *
****************************************************************************************/
        case 666:
            SendMainMenu(player, _creature);
            break;
        default:
            player->CLOSE_GOSSIP_MENU();
            return true;
        }

        if(action >= 100 && action < 200)
            SendMainMenu(player, _creature);

        if(action >= 200 && action < 300)
            SendSubMenu(player, _creature);

        return true;
    }
};

void AddSC_custom_npc_doctor()
{
    new custom_npc_doctor();
}