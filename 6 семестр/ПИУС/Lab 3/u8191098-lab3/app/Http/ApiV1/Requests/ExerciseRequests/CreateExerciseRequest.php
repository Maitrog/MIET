<?php

namespace App\Http\ApiV1\Requests\ExerciseRequests;

use Illuminate\Foundation\Http\FormRequest;

class CreateExerciseRequest extends FormRequest
{
    public function rules(): array
    {
        return [
            'name' => 'required|string|max:255|unique:exercises,name',
            'exercise_type_id' => 'required|exists:exercise_types,id',
            'muscle_group_id' => 'required|exists:muscle_groups,id',
        ];
    }
}
