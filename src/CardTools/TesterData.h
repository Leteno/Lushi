#pragma once

namespace CardTools {
    class TesterData {
        public:
            int mHealth, mAttack;
            TesterData(int health, int attack):
                mHealth(health),
                mAttack(attack)
            {
            }
        private:
    };
}