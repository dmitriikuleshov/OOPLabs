#ifndef VISITOR_HPP
#define VISITOR_HPP

#include "npc.hpp"
#include "npc_properties_config.hpp"
#include "npc_types.hpp"

class AttackerVisitor {
  public:
    virtual void visit(const ptr<NPC> &npc) = 0;
};

class AttackerVisitorWithConfig : public AttackerVisitor {
  protected:
    ptr<NpcPropertiesConfig> config;
    std::unordered_set<NpcType> enemies;
    std::string attacker_type_name;

  public:
    AttackerVisitorWithConfig(ptr<NpcPropertiesConfig> &conf,
                              const std::string type_name);
};

// Knight
class KnightAttackerVisitor : public AttackerVisitorWithConfig {
  public:
    KnightAttackerVisitor(ptr<NpcPropertiesConfig> &conf);

    KnightAttackerVisitor() = delete;

    static ptr<AttackerVisitor> create(ptr<NpcPropertiesConfig> &conf);

    void visit(const ptr<NPC> &npc) override;
};

// Frog
class FrogAttackerVisitor : public AttackerVisitorWithConfig {
  public:
    FrogAttackerVisitor(ptr<NpcPropertiesConfig> &conf);

    FrogAttackerVisitor() = delete;

    static ptr<AttackerVisitor> create(ptr<NpcPropertiesConfig> &conf);

    void visit(const ptr<NPC> &npc) override;
};

// Dragon
class DragonAttackerVisitor : public AttackerVisitorWithConfig {
  public:
    DragonAttackerVisitor(ptr<NpcPropertiesConfig> &conf);

    DragonAttackerVisitor() = delete;

    static ptr<AttackerVisitor> create(ptr<NpcPropertiesConfig> &conf);

    void visit(const ptr<NPC> &npc) override;
};

#endif // VISITOR_HPP