	

    /* Made by: aaddss A.K.A Deathsoul
       untested (in game)
    */
     
    #include "ScriptPCH.h"
     
    class Morph_npc : public CreatureScript
    {
    public:
        Morph_npc() : CreatureScript("Morph_npc") { }
     
     
        bool OnGossipHello(Player* player, Creature* creature)
        {
                    if (player->isInCombat())
                    {
                                            player->GetSession()->SendNotification(" You are in combat!");
                                            player->CLOSE_GOSSIP_MENU();
                                            return false;
                    }
     
                    player->ADD_GOSSIP_ITEM(6, "Broken", GOSSIP_SENDER_MAIN, 1);
                                    player->ADD_GOSSIP_ITEM(6, "Fel Orc", GOSSIP_SENDER_MAIN, 2);
                                    player->ADD_GOSSIP_ITEM(6, "Goblin", GOSSIP_SENDER_MAIN, 3);
                                    player->ADD_GOSSIP_ITEM(6, "Pandaren", GOSSIP_SENDER_MAIN, 4);
                                    player->ADD_GOSSIP_ITEM(6, "Worgen", GOSSIP_SENDER_MAIN, 5);
                                    player->ADD_GOSSIP_ITEM(6, "DeMorph", GOSSIP_SENDER_MAIN, 6);
                    player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,creature->GetGUID());
                    return true;
            }
           
            bool OnGossipSelect(Player* player, Creature* creature, uint32 uiSender, uint32 action)
            {
     
                    switch (action)
            {
                case 1:
                    player->CLOSE_GOSSIP_MENU();
                    player->SetDisplayId(21105);
                    break;
                case 2:
                    player->CLOSE_GOSSIP_MENU();
                    player->SetDisplayId(21267);
                    break;
                case 3:
                    player->CLOSE_GOSSIP_MENU();
                    player->SetDisplayId(20582);
                    break;
                case 4:
                    player->CLOSE_GOSSIP_MENU();
                    player->SetDisplayId(30414);
                    break;
                case 5:
                    player->CLOSE_GOSSIP_MENU();
                    player->SetDisplayId(26788);
                    break;
                case 6:
                    player->CLOSE_GOSSIP_MENU();
                    player->DeMorph();
                    break;
                    }
                    return true;
            }
    };
     
    void AddSC_Morph_npc()
    {
            new Morph_npc();
    }