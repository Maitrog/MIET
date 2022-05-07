<?php

namespace App\Domain\MuscleGroup\Actions;

use App\Models\MuscleGroup;

class CreateMuscleGroupAction
{
    public function execute(array $fields): MuscleGroup
    {
        return MuscleGroup::create($fields);
    }
}
