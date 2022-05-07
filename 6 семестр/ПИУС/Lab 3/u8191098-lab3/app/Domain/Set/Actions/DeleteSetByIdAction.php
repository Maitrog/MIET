<?php

namespace App\Domain\Set\Actions;

use App\Models\Set;

class DeleteSetByIdAction
{
    public function execute(int $setId)
    {
        $set = Set::findOrFail($setId);
        $set->delete();

        return $set;
    }
}
